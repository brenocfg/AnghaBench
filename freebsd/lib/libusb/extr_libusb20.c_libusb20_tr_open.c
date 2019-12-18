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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
 int libusb20_tr_open_stream (struct libusb20_transfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
libusb20_tr_open(struct libusb20_transfer *xfer, uint32_t MaxBufSize,
    uint32_t MaxFrameCount, uint8_t ep_no)
{
	return (libusb20_tr_open_stream(xfer, MaxBufSize, MaxFrameCount, ep_no, 0));
}