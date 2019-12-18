#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct QBUFFER {int data_len; scalar_t__ data; } ;
struct AdapterControlBlock {scalar_t__ adapter_type; int acb_flags; size_t wqbuf_firstindex; size_t wqbuf_lastindex; int /*<<< orphan*/ * wqbuffer; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ACB_ADAPTER_TYPE_B ; 
 int ACB_F_MESSAGE_WQBUFFER_READ ; 
 size_t ARCMSR_MAX_QBUFFER ; 
 int /*<<< orphan*/  arcmsr_Write_data_2iop_wqbuffer_D (struct AdapterControlBlock*) ; 
 struct QBUFFER* arcmsr_get_iop_wqbuffer (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_message_wrote (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_Write_data_2iop_wqbuffer(struct AdapterControlBlock *acb)
{
	u_int8_t *pQbuffer;
	struct QBUFFER *pwbuffer;
	u_int8_t *iop_data;
	int32_t allxfer_len=0;

	if(acb->adapter_type >= ACB_ADAPTER_TYPE_B) {
		arcmsr_Write_data_2iop_wqbuffer_D(acb);
		return;
	}
	if(acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_READ) {
		acb->acb_flags &= (~ACB_F_MESSAGE_WQBUFFER_READ);
		pwbuffer = arcmsr_get_iop_wqbuffer(acb);
		iop_data = (u_int8_t *)pwbuffer->data;
		while((acb->wqbuf_firstindex != acb->wqbuf_lastindex) 
			&& (allxfer_len < 124)) {
			pQbuffer = &acb->wqbuffer[acb->wqbuf_firstindex];
			*iop_data = *pQbuffer;
			acb->wqbuf_firstindex++;
			acb->wqbuf_firstindex %= ARCMSR_MAX_QBUFFER;
			iop_data++;
			allxfer_len++;
		}
		pwbuffer->data_len = allxfer_len;
		arcmsr_iop_message_wrote(acb);
	}
}