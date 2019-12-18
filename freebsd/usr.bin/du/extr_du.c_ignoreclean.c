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
struct ignentry {struct ignentry* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ignentry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ignentry*) ; 
 int /*<<< orphan*/  ignores ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
ignoreclean(void)
{
	struct ignentry *ign;

	while (!SLIST_EMPTY(&ignores)) {
		ign = SLIST_FIRST(&ignores);
		SLIST_REMOVE_HEAD(&ignores, next);
		free(ign->mask);
		free(ign);
	}
}