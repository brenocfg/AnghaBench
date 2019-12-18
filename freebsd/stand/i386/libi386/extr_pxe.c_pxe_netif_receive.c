#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  offset; scalar_t__ segment; } ;
struct TYPE_8__ {scalar_t__ FuncFlag; scalar_t__ Status; size_t FrameLength; scalar_t__ BufferLength; TYPE_1__ Frame; } ;
typedef  TYPE_2__ t_PXENV_UNDI_ISR ;

/* Variables and functions */
 int ETHER_ALIGN ; 
 int /*<<< orphan*/  PTOV (char*) ; 
 int /*<<< orphan*/  PXENV_UNDI_ISR ; 
 void* PXENV_UNDI_ISR_IN_GET_NEXT ; 
 scalar_t__ PXENV_UNDI_ISR_IN_PROCESS ; 
 scalar_t__ PXENV_UNDI_ISR_IN_START ; 
 scalar_t__ PXENV_UNDI_ISR_OUT_DONE ; 
 scalar_t__ PXENV_UNDI_ISR_OUT_RECEIVE ; 
 scalar_t__ PXENV_UNDI_ISR_OUT_TRANSMIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__* bio_alloc (int) ; 
 int /*<<< orphan*/  bio_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  pxe_call (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
pxe_netif_receive(void **pkt)
{
	t_PXENV_UNDI_ISR *isr;
	char *buf, *ptr, *frame;
	size_t size, rsize;

	isr = bio_alloc(sizeof(*isr));
	if (isr == NULL)
		return (-1);

	bzero(isr, sizeof(*isr));
	isr->FuncFlag = PXENV_UNDI_ISR_IN_START;
	pxe_call(PXENV_UNDI_ISR, isr);
	if (isr->Status != 0) {
		bio_free(isr, sizeof(*isr));
		return (-1);
	}

	bzero(isr, sizeof(*isr));
	isr->FuncFlag = PXENV_UNDI_ISR_IN_PROCESS;
	pxe_call(PXENV_UNDI_ISR, isr);
	if (isr->Status != 0) {
		bio_free(isr, sizeof(*isr));
		return (-1);
	}

	while (isr->FuncFlag == PXENV_UNDI_ISR_OUT_TRANSMIT) {
		/*
		 * Wait till transmit is done.
		 */
		bzero(isr, sizeof(*isr));
		isr->FuncFlag = PXENV_UNDI_ISR_IN_GET_NEXT;
		pxe_call(PXENV_UNDI_ISR, isr);
		if (isr->Status != 0 ||
		    isr->FuncFlag == PXENV_UNDI_ISR_OUT_DONE) {
			bio_free(isr, sizeof(*isr));
			return (-1);
		}
	}

	while (isr->FuncFlag != PXENV_UNDI_ISR_OUT_RECEIVE) {
		if (isr->Status != 0 ||
		    isr->FuncFlag == PXENV_UNDI_ISR_OUT_DONE) {
			bio_free(isr, sizeof(*isr));
			return (-1);
		}
		bzero(isr, sizeof(*isr));
		isr->FuncFlag = PXENV_UNDI_ISR_IN_GET_NEXT;
		pxe_call(PXENV_UNDI_ISR, isr);
	}

	size = isr->FrameLength;
	buf = malloc(size + ETHER_ALIGN);
	if (buf == NULL) {
		bio_free(isr, sizeof(*isr));
		return (-1);
	}
	ptr = buf + ETHER_ALIGN;
	rsize = 0;

	while (rsize < size) {
		frame = (char *)((uintptr_t)isr->Frame.segment << 4);
		frame += isr->Frame.offset;
		bcopy(PTOV(frame), ptr, isr->BufferLength);
		ptr += isr->BufferLength;
		rsize += isr->BufferLength;

		bzero(isr, sizeof(*isr));
		isr->FuncFlag = PXENV_UNDI_ISR_IN_GET_NEXT;
		pxe_call(PXENV_UNDI_ISR, isr);
		if (isr->Status != 0) {
			bio_free(isr, sizeof(*isr));
			free(buf);
			return (-1);
		}

		/* Did we got another update? */
		if (isr->FuncFlag == PXENV_UNDI_ISR_OUT_RECEIVE)
			continue;
		break;
	}

	*pkt = buf;
	bio_free(isr, sizeof(*isr));
	return (rsize);
}