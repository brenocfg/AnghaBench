#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct libusb20_transfer {int is_opened; int maxFrames; int /*<<< orphan*/ * pLength; int /*<<< orphan*/ * ppBuffer; TYPE_2__* pdev; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int (* tr_open ) (struct libusb20_transfer*,int,int,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int LIBUSB20_ERROR_BUSY ; 
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int LIBUSB20_ERROR_NO_MEM ; 
 int LIBUSB20_MAX_FRAME_PRE_SCALE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct libusb20_transfer*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct libusb20_transfer*,int,int,int,int /*<<< orphan*/ ,int) ; 

int
libusb20_tr_open_stream(struct libusb20_transfer *xfer, uint32_t MaxBufSize,
    uint32_t MaxFrameCount, uint8_t ep_no, uint16_t stream_id)
{
	uint32_t size;
	uint8_t pre_scale;
	int error;

	if (xfer->is_opened)
		return (LIBUSB20_ERROR_BUSY);
	if (MaxFrameCount & LIBUSB20_MAX_FRAME_PRE_SCALE) {
		MaxFrameCount &= ~LIBUSB20_MAX_FRAME_PRE_SCALE;
		/*
		 * The kernel can setup 8 times more frames when
		 * pre-scaling ISOCHRONOUS transfers. Make sure the
		 * length and pointer buffers are big enough:
		 */
		MaxFrameCount *= 8;
		pre_scale = 1;
	} else {
		pre_scale = 0;
	}
	if (MaxFrameCount == 0)
		return (LIBUSB20_ERROR_INVALID_PARAM);

	xfer->maxFrames = MaxFrameCount;

	size = MaxFrameCount * sizeof(xfer->pLength[0]);
	xfer->pLength = malloc(size);
	if (xfer->pLength == NULL) {
		return (LIBUSB20_ERROR_NO_MEM);
	}
	memset(xfer->pLength, 0, size);

	size = MaxFrameCount * sizeof(xfer->ppBuffer[0]);
	xfer->ppBuffer = malloc(size);
	if (xfer->ppBuffer == NULL) {
		free(xfer->pLength);
		return (LIBUSB20_ERROR_NO_MEM);
	}
	memset(xfer->ppBuffer, 0, size);

	if (pre_scale) {
		error = xfer->pdev->methods->tr_open(xfer, MaxBufSize,
		    MaxFrameCount / 8, ep_no, stream_id, 1);
	} else {
		error = xfer->pdev->methods->tr_open(xfer, MaxBufSize,
		    MaxFrameCount, ep_no, stream_id, 0);
	}

	if (error) {
		free(xfer->ppBuffer);
		free(xfer->pLength);
	} else {
		xfer->is_opened = 1;
	}
	return (error);
}