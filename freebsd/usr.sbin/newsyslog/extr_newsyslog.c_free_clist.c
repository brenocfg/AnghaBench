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
struct conf_entry {int dummy; } ;
struct cflist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (struct cflist*) ; 
 struct conf_entry* STAILQ_FIRST (struct cflist*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct cflist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_nextp ; 
 int /*<<< orphan*/  free (struct cflist*) ; 
 int /*<<< orphan*/  free_entry (struct conf_entry*) ; 

__attribute__((used)) static void
free_clist(struct cflist *list)
{
	struct conf_entry *ent;

	while (!STAILQ_EMPTY(list)) {
		ent = STAILQ_FIRST(list);
		STAILQ_REMOVE_HEAD(list, cf_nextp);
		free_entry(ent);
	}

	free(list);
	list = NULL;
}