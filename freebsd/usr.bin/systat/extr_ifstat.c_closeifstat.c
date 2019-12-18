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
struct if_stat {int dummy; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct if_stat* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curlist ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct if_stat*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  wclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
closeifstat(WINDOW *w)
{
	struct if_stat	*node = NULL;

	while (!SLIST_EMPTY(&curlist)) {
		node = SLIST_FIRST(&curlist);
		SLIST_REMOVE_HEAD(&curlist, link);
		free(node);
	}

	if (w != NULL) {
		wclear(w);
		wrefresh(w);
		delwin(w);
	}

	return;
}