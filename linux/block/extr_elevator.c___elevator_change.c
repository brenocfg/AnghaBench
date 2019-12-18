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
struct request_queue {TYPE_1__* elevator; } ;
struct elevator_type {int dummy; } ;
typedef  int /*<<< orphan*/  elevator_name ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELV_NAME_MAX ; 
 int ENOENT ; 
 int /*<<< orphan*/  blk_queue_registered (struct request_queue*) ; 
 struct elevator_type* elevator_get (struct request_queue*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ elevator_match (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elevator_put (struct elevator_type*) ; 
 int elevator_switch (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strstrip (char*) ; 

__attribute__((used)) static int __elevator_change(struct request_queue *q, const char *name)
{
	char elevator_name[ELV_NAME_MAX];
	struct elevator_type *e;

	/* Make sure queue is not in the middle of being removed */
	if (!blk_queue_registered(q))
		return -ENOENT;

	/*
	 * Special case for mq, turn off scheduling
	 */
	if (!strncmp(name, "none", 4)) {
		if (!q->elevator)
			return 0;
		return elevator_switch(q, NULL);
	}

	strlcpy(elevator_name, name, sizeof(elevator_name));
	e = elevator_get(q, strstrip(elevator_name), true);
	if (!e)
		return -EINVAL;

	if (q->elevator &&
	    elevator_match(q->elevator->type, elevator_name, 0)) {
		elevator_put(e);
		return 0;
	}

	return elevator_switch(q, e);
}