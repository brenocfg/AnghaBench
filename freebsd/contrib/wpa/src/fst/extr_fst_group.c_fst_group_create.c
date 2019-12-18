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
struct fst_group {int /*<<< orphan*/  global_groups_lentry; int /*<<< orphan*/  group_id; int /*<<< orphan*/  ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,struct fst_group*) ; 
 int /*<<< orphan*/  fst_global_groups_list ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fst_printf_group (struct fst_group*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  on_group_created ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct fst_group* os_zalloc (int) ; 

struct fst_group * fst_group_create(const char *group_id)
{
	struct fst_group *g;

	g = os_zalloc(sizeof(*g));
	if (g == NULL) {
		fst_printf(MSG_ERROR, "%s: Cannot alloc group", group_id);
		return NULL;
	}

	dl_list_init(&g->ifaces);
	os_strlcpy(g->group_id, group_id, sizeof(g->group_id));

	dl_list_add_tail(&fst_global_groups_list, &g->global_groups_lentry);
	fst_printf_group(g, MSG_DEBUG, "instance created");

	foreach_fst_ctrl_call(on_group_created, g);

	return g;
}