#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  assigns; } ;
typedef  TYPE_1__ git_attr_rule ;
struct TYPE_6__ {char const* name; int /*<<< orphan*/  name_hash; } ;
typedef  TYPE_2__ git_attr_name ;
typedef  int /*<<< orphan*/  git_attr_assignment ;

/* Variables and functions */
 int /*<<< orphan*/  git_attr_file__name_hash (char const*) ; 
 scalar_t__ git_vector_bsearch (size_t*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * git_vector_get (int /*<<< orphan*/ *,size_t) ; 

git_attr_assignment *git_attr_rule__lookup_assignment(
	git_attr_rule *rule, const char *name)
{
	size_t pos;
	git_attr_name key;
	key.name = name;
	key.name_hash = git_attr_file__name_hash(name);

	if (git_vector_bsearch(&pos, &rule->assigns, &key))
		return NULL;

	return git_vector_get(&rule->assigns, pos);
}