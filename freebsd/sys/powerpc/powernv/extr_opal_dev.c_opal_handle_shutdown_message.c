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
struct opal_msg {int /*<<< orphan*/ * params; } ;

/* Variables and functions */
#define  OPAL_SOFT_OFF 129 
#define  OPAL_SOFT_REBOOT 128 
 int RB_POWEROFF ; 
 int RB_REROOT ; 
 int be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_nice (int) ; 

__attribute__((used)) static void
opal_handle_shutdown_message(void *unused, struct opal_msg *msg)
{
	int howto;

	switch (be64toh(msg->params[0])) {
	case OPAL_SOFT_OFF:
		howto = RB_POWEROFF;
		break;
	case OPAL_SOFT_REBOOT:
		howto = RB_REROOT;
		break;
	}
	shutdown_nice(howto);
}