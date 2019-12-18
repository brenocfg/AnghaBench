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
struct audit_event_map {int dummy; } ;

/* Variables and functions */
 struct audit_event_map* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct audit_event_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_event_map_free (struct audit_event_map*) ; 
 int /*<<< orphan*/  ev_cache ; 
 int /*<<< orphan*/  ev_list ; 

__attribute__((used)) static void
flush_cache(void)
{
	struct audit_event_map *aemp;

	/* XXX: Would assert 'mutex'. */

	while ((aemp = LIST_FIRST(&ev_cache)) != NULL) {
		LIST_REMOVE(aemp, ev_list);
		audit_event_map_free(aemp);
	}
}