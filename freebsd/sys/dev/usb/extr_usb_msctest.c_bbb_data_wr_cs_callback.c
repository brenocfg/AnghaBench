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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_DATA_WR ; 
 int /*<<< orphan*/  ST_STATUS ; 
 int /*<<< orphan*/  bbb_data_clear_stall_callback (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbb_data_wr_cs_callback(struct usb_xfer *xfer, usb_error_t error)
{
	bbb_data_clear_stall_callback(xfer, ST_STATUS,
	    ST_DATA_WR);
}