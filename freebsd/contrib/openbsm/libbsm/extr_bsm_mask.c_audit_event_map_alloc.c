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
struct TYPE_2__ {int /*<<< orphan*/  ae_desc; int /*<<< orphan*/  ae_name; } ;
struct audit_event_map {int /*<<< orphan*/  ev_desc; TYPE_1__ ev; int /*<<< orphan*/  ev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct audit_event_map*,int) ; 
 struct audit_event_map* malloc (int) ; 

__attribute__((used)) static struct audit_event_map *
audit_event_map_alloc(void)
{
	struct audit_event_map *aemp;

	aemp = malloc(sizeof(*aemp));
	if (aemp == NULL)
		return (aemp);
	bzero(aemp, sizeof(*aemp));
	aemp->ev.ae_name = aemp->ev_name;
	aemp->ev.ae_desc = aemp->ev_desc;
	return (aemp);
}