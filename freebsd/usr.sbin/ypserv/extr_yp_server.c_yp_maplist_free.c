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
struct ypmaplist {struct ypmaplist* map; struct ypmaplist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ypmaplist*) ; 

__attribute__((used)) static void yp_maplist_free(struct ypmaplist *yp_maplist)
{
	register struct ypmaplist *next;

	while (yp_maplist) {
		next = yp_maplist->next;
		free(yp_maplist->map);
		free(yp_maplist);
		yp_maplist = next;
	}
	return;
}