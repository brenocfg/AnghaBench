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
struct pt_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct pt_event *pt_event_init(struct pt_event *event)
{
	if (event)
		memset(event, 0, sizeof(*event));

	return event;
}