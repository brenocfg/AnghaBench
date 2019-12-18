#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct apple_state {int dummy; } ;
typedef  scalar_t__ hid_device_p ;
typedef  TYPE_1__* bthid_session_p ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 scalar_t__ MAGIC_MOUSE (scalar_t__) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ get_hid_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int*,int) ; 

void
hid_initialise(bthid_session_p s)
{
	hid_device_p hid_device = get_hid_device(&s->bdaddr);

	if (hid_device && MAGIC_MOUSE(hid_device)) {
		/* Magic report to enable trackpad on Apple's Magic Mouse */
		static uint8_t rep[] = {0x53, 0xd7, 0x01};

		if ((s->ctx = calloc(1, sizeof(struct apple_state))) == NULL)
			return;
		write(s->ctrl, rep, 3);
	}
}