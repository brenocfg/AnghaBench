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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct libusb20_transfer {int* pLength; int nFrames; void** ppBuffer; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 void* libusb20_pass_ptr (void*) ; 

void
libusb20_tr_setup_control(struct libusb20_transfer *xfer, void *psetup, void *pBuf, uint32_t timeout)
{
	uint16_t len;

	xfer->ppBuffer[0] = libusb20_pass_ptr(psetup);
	xfer->pLength[0] = 8;		/* fixed */
	xfer->timeout = timeout;

	len = ((uint8_t *)psetup)[6] | (((uint8_t *)psetup)[7] << 8);

	if (len != 0) {
		xfer->nFrames = 2;
		xfer->ppBuffer[1] = libusb20_pass_ptr(pBuf);
		xfer->pLength[1] = len;
	} else {
		xfer->nFrames = 1;
	}
	return;
}