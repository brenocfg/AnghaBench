#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cn_children; } ;
typedef  TYPE_1__ cd9660node ;

/* Variables and functions */
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_next_child ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
cd9660_free_structure(cd9660node *root)
{
	cd9660node *cn;

	while ((cn = TAILQ_FIRST(&root->cn_children)) != NULL) {
		TAILQ_REMOVE(&root->cn_children, cn, cn_next_child);
		cd9660_free_structure(cn);
	}
	free(root);
}