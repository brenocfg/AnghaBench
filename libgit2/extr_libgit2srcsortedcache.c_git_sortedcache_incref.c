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
typedef  int /*<<< orphan*/  git_sortedcache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 

void git_sortedcache_incref(git_sortedcache *sc)
{
	GIT_REFCOUNT_INC(sc);
}