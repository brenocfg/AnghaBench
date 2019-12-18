#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
typedef  long u_int32_t ;
typedef  int u_int16_t ;
struct aac_softc {int aac_max_msix; int aac_fibs_pushed_no; scalar_t__* aac_rrq_outstanding; scalar_t__ aac_vector_cap; int flags; scalar_t__ msi_enabled; } ;
struct aac_fib_xporthdr {int Handle; int HostAddress; int Size; } ;
struct aac_command {int cm_fibphys; TYPE_3__* cm_fib; } ;
struct TYPE_4__ {long TimeStamp; long SenderFibAddressHigh; } ;
struct TYPE_5__ {scalar_t__ Command; int Handle; int Size; long SenderFibAddress; TYPE_1__ u; int /*<<< orphan*/  StructType; } ;
struct TYPE_6__ {TYPE_2__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_FIBTYPE_TFIB2 ; 
 int /*<<< orphan*/  AAC_FIBTYPE_TFIB2_64 ; 
 int AAC_FLAGS_NEW_COMM_TYPE2 ; 
 int /*<<< orphan*/  AAC_MEM0_SETREG4 (struct aac_softc*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  AAC_SRC_IQUE32 ; 
 int /*<<< orphan*/  AAC_SRC_IQUE64_H ; 
 int /*<<< orphan*/  AAC_SRC_IQUE64_L ; 
 scalar_t__ AifRequest ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_enqueue_busy (struct aac_command*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_src_send_command(struct aac_softc *sc, struct aac_command *cm)
{
	struct aac_fib_xporthdr *pFibX;
	u_int32_t fibsize, high_addr;
	u_int64_t address;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "send command (new comm. type1)");

	if (sc->msi_enabled && cm->cm_fib->Header.Command != AifRequest &&
		sc->aac_max_msix > 1) { 
		u_int16_t vector_no, first_choice = 0xffff;
	
		vector_no = sc->aac_fibs_pushed_no % sc->aac_max_msix;
		do {
			vector_no += 1;
			if (vector_no == sc->aac_max_msix)
				vector_no = 1;
			if (sc->aac_rrq_outstanding[vector_no] < 
				sc->aac_vector_cap)
				break;
			if (0xffff == first_choice)
				first_choice = vector_no;
			else if (vector_no == first_choice)
				break;
		} while (1);
		if (vector_no == first_choice)
			vector_no = 0;
		sc->aac_rrq_outstanding[vector_no]++;
		if (sc->aac_fibs_pushed_no == 0xffffffff)
			sc->aac_fibs_pushed_no = 0;
		else
			sc->aac_fibs_pushed_no++; 
		
		cm->cm_fib->Header.Handle += (vector_no << 16);
	}		

	if (sc->flags & AAC_FLAGS_NEW_COMM_TYPE2) {
		/* Calculate the amount to the fibsize bits */
		fibsize = (cm->cm_fib->Header.Size + 127) / 128 - 1; 
		/* Fill new FIB header */
		address = cm->cm_fibphys;
		high_addr = (u_int32_t)(address >> 32);
		if (high_addr == 0L) {
			cm->cm_fib->Header.StructType = AAC_FIBTYPE_TFIB2;
			cm->cm_fib->Header.u.TimeStamp = 0L;
		} else {
			cm->cm_fib->Header.StructType = AAC_FIBTYPE_TFIB2_64;
			cm->cm_fib->Header.u.SenderFibAddressHigh = high_addr;
		}
		cm->cm_fib->Header.SenderFibAddress = (u_int32_t)address;
	} else {
		/* Calculate the amount to the fibsize bits */
		fibsize = (sizeof(struct aac_fib_xporthdr) + 
		   cm->cm_fib->Header.Size + 127) / 128 - 1; 
		/* Fill XPORT header */ 
		pFibX = (struct aac_fib_xporthdr *)
			((unsigned char *)cm->cm_fib - sizeof(struct aac_fib_xporthdr));
		pFibX->Handle = cm->cm_fib->Header.Handle;
		pFibX->HostAddress = cm->cm_fibphys;
		pFibX->Size = cm->cm_fib->Header.Size;
		address = cm->cm_fibphys - sizeof(struct aac_fib_xporthdr);
		high_addr = (u_int32_t)(address >> 32);
	}

	if (fibsize > 31) 
		fibsize = 31;
	aac_enqueue_busy(cm);
	if (high_addr) {
		AAC_MEM0_SETREG4(sc, AAC_SRC_IQUE64_H, high_addr);
		AAC_MEM0_SETREG4(sc, AAC_SRC_IQUE64_L, (u_int32_t)address + fibsize);
	} else {
		AAC_MEM0_SETREG4(sc, AAC_SRC_IQUE32, (u_int32_t)address + fibsize);
	}
	return 0;
}