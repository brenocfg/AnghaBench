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
struct catentry {struct catentry* lang; struct catentry* path; struct catentry* name; struct catentry* catd; scalar_t__ __size; int /*<<< orphan*/  __data; } ;

/* Variables and functions */
 struct catentry* NLERR ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct catentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache ; 
 int /*<<< orphan*/  catentry ; 
 int /*<<< orphan*/  free (struct catentry*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
catfree(struct catentry *np)
{

	if (np->catd != NULL && np->catd != NLERR) {
		munmap(np->catd->__data, (size_t)np->catd->__size);
		free(np->catd);
	}
	SLIST_REMOVE(&cache, np, catentry, list);
	free(np->name);
	free(np->path);
	free(np->lang);
	free(np);
}