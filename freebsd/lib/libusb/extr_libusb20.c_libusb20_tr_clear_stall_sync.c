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
struct libusb20_transfer {TYPE_2__* pdev; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tr_clear_stall_sync ) (struct libusb20_transfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct libusb20_transfer*) ; 

void
libusb20_tr_clear_stall_sync(struct libusb20_transfer *xfer)
{
	xfer->pdev->methods->tr_clear_stall_sync(xfer);
	return;
}