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

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  add_ref_to_list ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_commit_graph (char const*,int /*<<< orphan*/ *,struct string_list*,int,int) ; 

void write_commit_graph_reachable(const char *obj_dir, int append,
				  int report_progress)
{
	struct string_list list = STRING_LIST_INIT_DUP;

	for_each_ref(add_ref_to_list, &list);
	write_commit_graph(obj_dir, NULL, &list, append, report_progress);

	string_list_clear(&list, 0);
}