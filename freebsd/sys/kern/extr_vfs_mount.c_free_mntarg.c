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
struct mntarg {struct mntarg* v; int /*<<< orphan*/  list; } ;
struct mntaarg {struct mntaarg* v; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct mntarg* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mntarg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
free_mntarg(struct mntarg *ma)
{
	struct mntaarg *maa;

	while (!SLIST_EMPTY(&ma->list)) {
		maa = SLIST_FIRST(&ma->list);
		SLIST_REMOVE_HEAD(&ma->list, next);
		free(maa, M_MOUNT);
	}
	free(ma->v, M_MOUNT);
	free(ma, M_MOUNT);
}