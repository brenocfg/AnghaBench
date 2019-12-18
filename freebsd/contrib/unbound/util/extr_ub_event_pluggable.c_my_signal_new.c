#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ub_event_base {int dummy; } ;
struct ub_event {int /*<<< orphan*/ * vmt; int /*<<< orphan*/  magic; } ;
struct my_event {struct ub_event super; int /*<<< orphan*/  ev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  NATIVE_BITS_CB (void (*) (int,short,void*)) ; 
 int /*<<< orphan*/  UB_EVENT_MAGIC ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  default_event_vmt ; 
 scalar_t__ event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct my_event*) ; 
 int /*<<< orphan*/  signal_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct ub_event*
my_signal_new(struct ub_event_base* base, int fd,
	void (*cb)(int, short, void*), void* arg)
{
	struct my_event *my_ev = (struct my_event*)calloc(1,
		sizeof(struct my_event));

	if (!my_ev)
		return NULL;

	signal_set(&my_ev->ev, fd, NATIVE_BITS_CB(cb), arg);
	if (event_base_set(AS_MY_EVENT_BASE(base)->base, &my_ev->ev) != 0) {
		free(my_ev);
		return NULL;
	}
	my_ev->super.magic = UB_EVENT_MAGIC;
	my_ev->super.vmt = &default_event_vmt;
	return &my_ev->super;
}