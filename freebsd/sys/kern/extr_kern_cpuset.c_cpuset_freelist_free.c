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
struct setlist {int dummy; } ;
struct cpuset {int dummy; } ;

/* Variables and functions */
 struct cpuset* LIST_FIRST (struct setlist*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_zone ; 
 int /*<<< orphan*/  cs_link ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct cpuset*) ; 

__attribute__((used)) static void
cpuset_freelist_free(struct setlist *list)
{
	struct cpuset *set;

	while ((set = LIST_FIRST(list)) != NULL) {
		LIST_REMOVE(set, cs_link);
		uma_zfree(cpuset_zone, set);
	}
}