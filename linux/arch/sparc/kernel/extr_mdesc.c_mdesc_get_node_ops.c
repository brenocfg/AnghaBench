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
typedef  int /*<<< orphan*/ * mdesc_node_match_f ;
typedef  int /*<<< orphan*/ * mdesc_node_info_rel_f ;
typedef  int /*<<< orphan*/ * mdesc_node_info_get_f ;
struct TYPE_2__ {int /*<<< orphan*/ * node_match; int /*<<< orphan*/ * rel_info; int /*<<< orphan*/ * get_info; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* md_node_ops_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void mdesc_get_node_ops(const char *node_name,
			       mdesc_node_info_get_f *get_info_f,
			       mdesc_node_info_rel_f *rel_info_f,
			       mdesc_node_match_f *match_f)
{
	int i;

	if (get_info_f)
		*get_info_f = NULL;

	if (rel_info_f)
		*rel_info_f = NULL;

	if (match_f)
		*match_f = NULL;

	if (!node_name)
		return;

	for (i = 0; md_node_ops_table[i].name != NULL; i++) {
		if (strcmp(md_node_ops_table[i].name, node_name) == 0) {
			if (get_info_f)
				*get_info_f = md_node_ops_table[i].get_info;

			if (rel_info_f)
				*rel_info_f = md_node_ops_table[i].rel_info;

			if (match_f)
				*match_f = md_node_ops_table[i].node_match;

			break;
		}
	}
}