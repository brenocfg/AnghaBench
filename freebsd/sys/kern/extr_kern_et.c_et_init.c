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
struct eventtimer {int et_active; void* et_arg; int /*<<< orphan*/ * et_deregister_cb; int /*<<< orphan*/ * et_event_cb; } ;
typedef  int /*<<< orphan*/  et_event_cb_t ;
typedef  int /*<<< orphan*/  et_deregister_cb_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 

int
et_init(struct eventtimer *et, et_event_cb_t *event,
    et_deregister_cb_t *deregister, void *arg)
{

	if (event == NULL)
		return (EINVAL);
	if (et->et_active)
		return (EBUSY);

	et->et_active = 1;
	et->et_event_cb = event;
	et->et_deregister_cb = deregister;
	et->et_arg = arg;
	return (0);
}