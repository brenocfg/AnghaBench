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
struct audit_event_map {int /*<<< orphan*/  ev; } ;
struct au_event_ent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct audit_event_map*,int /*<<< orphan*/ ) ; 
 struct audit_event_map* audit_event_map_alloc () ; 
 int /*<<< orphan*/  audit_event_map_free (struct audit_event_map*) ; 
 int /*<<< orphan*/  ev_cache ; 
 int /*<<< orphan*/  ev_list ; 
 int /*<<< orphan*/  flush_cache () ; 
 struct au_event_ent* getauevent_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setauevent () ; 

__attribute__((used)) static int
load_event_table(void)
{
	struct audit_event_map *aemp;
	struct au_event_ent *ep;

	/*
	 * XXX: Would assert 'mutex'.
	 * Loading of the cache happens only once; dont check if cache is
	 * already loaded.
	 */
	LIST_INIT(&ev_cache);
	setauevent();	/* Rewind to beginning of entries. */
	do {
		aemp = audit_event_map_alloc();
		if (aemp == NULL) {
			flush_cache();
			return (-1);
		}
		ep = getauevent_r(&aemp->ev);
		if (ep != NULL)
			LIST_INSERT_HEAD(&ev_cache, aemp, ev_list);
		else
			audit_event_map_free(aemp);
	} while (ep != NULL);
	return (1);
}