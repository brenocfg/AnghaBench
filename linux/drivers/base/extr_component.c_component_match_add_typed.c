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
struct device {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (struct device*,int,void*),void*) ; 

void component_match_add_typed(struct device *master,
	struct component_match **matchptr,
	int (*compare_typed)(struct device *, int, void *), void *compare_data)
{
	__component_match_add(master, matchptr, NULL, NULL, compare_typed,
			      compare_data);
}