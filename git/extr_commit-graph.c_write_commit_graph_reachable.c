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
struct string_list {int dummy; } ;
struct split_commit_graph_opts {int dummy; } ;
typedef  enum commit_graph_write_flags { ____Placeholder_commit_graph_write_flags } commit_graph_write_flags ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  add_ref_to_list ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int write_commit_graph (char const*,int /*<<< orphan*/ *,struct string_list*,int,struct split_commit_graph_opts const*) ; 

int write_commit_graph_reachable(const char *obj_dir,
				 enum commit_graph_write_flags flags,
				 const struct split_commit_graph_opts *split_opts)
{
	struct string_list list = STRING_LIST_INIT_DUP;
	int result;

	for_each_ref(add_ref_to_list, &list);
	result = write_commit_graph(obj_dir, NULL, &list,
				    flags, split_opts);

	string_list_clear(&list, 0);
	return result;
}