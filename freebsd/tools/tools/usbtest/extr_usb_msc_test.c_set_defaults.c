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
struct usb_msc_params {int duration; int try_invalid_scsi_command; int try_invalid_wrapper_block; int try_last_lba; int max_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct usb_msc_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_defaults(struct usb_msc_params *p)
{
	memset(p, 0, sizeof(*p));

	p->duration = 60;		/* seconds */
	p->try_invalid_scsi_command = 1;
	p->try_invalid_wrapper_block = 1;
	p->try_last_lba = 1;
	p->max_errors = -1;
}