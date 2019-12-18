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
struct snapdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct snapdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_link ; 
 int /*<<< orphan*/  snapfree ; 
 int /*<<< orphan*/  snapfree_lock ; 

__attribute__((used)) static void
ffs_snapdata_free(struct snapdata *sn)
{
	mtx_lock(&snapfree_lock);
	LIST_INSERT_HEAD(&snapfree, sn, sn_link);
	mtx_unlock(&snapfree_lock);
}