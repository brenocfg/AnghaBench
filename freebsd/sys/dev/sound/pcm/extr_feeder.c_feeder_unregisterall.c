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
struct feedertab_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FEEDER ; 
 struct feedertab_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct feedertab_entry* SLIST_NEXT (struct feedertab_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feedertab ; 
 int /*<<< orphan*/  free (struct feedertab_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
feeder_unregisterall(void *p)
{
	struct feedertab_entry *fte, *next;

	next = SLIST_FIRST(&feedertab);
	while (next != NULL) {
		fte = next;
		next = SLIST_NEXT(fte, link);
		free(fte, M_FEEDER);
	}
}