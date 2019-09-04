#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_list_insert (int /*<<< orphan*/ ,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 int /*<<< orphan*/  get_commit_reference (char const*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  reduce_heads_replace (struct commit_list**) ; 

__attribute__((used)) static int handle_independent(int count, const char **args)
{
	struct commit_list *revs = NULL, *rev;
	int i;

	for (i = count - 1; i >= 0; i--)
		commit_list_insert(get_commit_reference(args[i]), &revs);

	reduce_heads_replace(&revs);

	if (!revs)
		return 1;

	for (rev = revs; rev; rev = rev->next)
		printf("%s\n", oid_to_hex(&rev->item->object.oid));

	free_commit_list(revs);
	return 0;
}