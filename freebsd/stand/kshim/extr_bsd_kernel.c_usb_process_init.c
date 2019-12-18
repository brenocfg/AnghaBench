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
typedef  size_t uint8_t ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 size_t USB_PROC_MAX ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_proc_mtx ; 
 int /*<<< orphan*/ * usb_process ; 
 int /*<<< orphan*/  usb_process_init_sub (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_process_init(void *arg)
{
	uint8_t x;

	mtx_init(&usb_proc_mtx, "usb-proc-mtx", NULL, MTX_DEF | MTX_RECURSE);

	for (x = 0; x != USB_PROC_MAX; x++)
		usb_process_init_sub(&usb_process[x]);

}