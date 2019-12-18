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
 int /*<<< orphan*/  UMASS_T_CBI_DATA_READ ; 
 int /*<<< orphan*/  UMASS_T_CBI_RESET3 ; 
 int /*<<< orphan*/  umass_t_cbi_data_clear_stall_callback (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umass_t_cbi_reset2_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_cbi_data_clear_stall_callback(xfer, UMASS_T_CBI_RESET3,
	    UMASS_T_CBI_DATA_READ, error);
}