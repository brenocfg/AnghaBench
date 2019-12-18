#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ancestor; } ;
typedef  TYPE_1__ checkout_conflictdata ;

/* Variables and functions */
 int checkout_conflicts_cmp_entry (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_conflicts_cmp_ancestor(const void *p, const void *c)
{
	const char *path = p;
	const checkout_conflictdata *conflict = c;

	if (!conflict->ancestor)
		return 1;

	return checkout_conflicts_cmp_entry(path, conflict->ancestor);
}