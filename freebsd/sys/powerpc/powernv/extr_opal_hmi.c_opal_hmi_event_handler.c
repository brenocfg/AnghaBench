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
struct opal_msg {int /*<<< orphan*/  params; } ;
struct opal_hmi_event {int severity; int type; scalar_t__ disposition; int /*<<< orphan*/  pir; int /*<<< orphan*/  hmer; } ;
typedef  int /*<<< orphan*/  evt ;

/* Variables and functions */
 scalar_t__ HMI_DISP_NOT_RECOVERED ; 
 int /*<<< orphan*/  memcpy (struct opal_hmi_event*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
opal_hmi_event_handler(void *unused, struct opal_msg *msg)
{
	struct opal_hmi_event	evt;

	memcpy(&evt, &msg->params, sizeof(evt));
	printf("Hypervisor Maintenance Event received"
	    "(Severity %d, type %d, HMER: %016lx).\n",
	    evt.severity, evt.type, evt.hmer);

	if (evt.disposition == HMI_DISP_NOT_RECOVERED)
		panic("Unrecoverable hypervisor maintenance exception on CPU %d",
		    evt.pir);

	return;
}