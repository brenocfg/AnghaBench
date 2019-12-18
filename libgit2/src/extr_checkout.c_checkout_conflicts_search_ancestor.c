#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  update_conflicts; } ;
typedef  TYPE_1__ checkout_data ;
typedef  int /*<<< orphan*/  checkout_conflictdata ;

/* Variables and functions */
 int /*<<< orphan*/  checkout_conflicts_cmp_ancestor ; 
 scalar_t__ git_vector_bsearch2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * git_vector_get (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static checkout_conflictdata *checkout_conflicts_search_ancestor(
	checkout_data *data,
	const char *path)
{
	size_t pos;

	if (git_vector_bsearch2(&pos, &data->update_conflicts, checkout_conflicts_cmp_ancestor, path) < 0)
		return NULL;

	return git_vector_get(&data->update_conflicts, pos);
}