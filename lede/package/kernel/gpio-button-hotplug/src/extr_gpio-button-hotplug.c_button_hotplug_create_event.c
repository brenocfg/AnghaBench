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
struct bh_event {char const* name; unsigned int type; unsigned long seen; char* action; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_DBG (char*,char const*,unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ button_hotplug_work ; 
 struct bh_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int button_hotplug_create_event(const char *name, unsigned int type,
		unsigned long seen, int pressed)
{
	struct bh_event *event;

	BH_DBG("create event, name=%s, seen=%lu, pressed=%d\n",
		name, seen, pressed);

	event = kzalloc(sizeof(*event), GFP_KERNEL);
	if (!event)
		return -ENOMEM;

	event->name = name;
	event->type = type;
	event->seen = seen;
	event->action = pressed ? "pressed" : "released";

	INIT_WORK(&event->work, (void *)(void *)button_hotplug_work);
	schedule_work(&event->work);

	return 0;
}