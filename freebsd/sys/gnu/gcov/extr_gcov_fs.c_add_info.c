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
struct gcov_node {int num_loaded; struct gcov_info** loaded_info; struct gcov_info* unloaded_info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  M_GCOV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct gcov_info**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_filename (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_info_is_compatible (struct gcov_info*,struct gcov_info*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct gcov_info** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct gcov_info**,struct gcov_info**,int) ; 

__attribute__((used)) static void
add_info(struct gcov_node *node, struct gcov_info *info)
{
	struct gcov_info **loaded_info;
	int num = node->num_loaded;

	/*
	 * Prepare new array. This is done first to simplify cleanup in
	 * case the new data set is incompatible, the node only contains
	 * unloaded data sets and there's not enough memory for the array.
	 */
	loaded_info = malloc((num + 1)* sizeof(struct gcov_info *), M_GCOV, M_NOWAIT|M_ZERO);
	if (!loaded_info) {
		log(LOG_WARNING, "could not add '%s' (out of memory)\n",
			gcov_info_filename(info));
		return;
	}
	memcpy(loaded_info, node->loaded_info,
	       num * sizeof(struct gcov_info *));
	loaded_info[num] = info;
	/* Check if the new data set is compatible. */
	if (num == 0) {
		/*
		 * A module was unloaded, modified and reloaded. The new
		 * data set replaces the copy of the last one.
		 */
		if (!gcov_info_is_compatible(node->unloaded_info, info)) {
			log(LOG_WARNING, "discarding saved data for %s "
				"(incompatible version)\n",
				gcov_info_filename(info));
			gcov_info_free(node->unloaded_info);
			node->unloaded_info = NULL;
		}
	} else {
		/*
		 * Two different versions of the same object file are loaded.
		 * The initial one takes precedence.
		 */
		if (!gcov_info_is_compatible(node->loaded_info[0], info)) {
			log(LOG_WARNING, "could not add '%s' (incompatible "
				"version)\n", gcov_info_filename(info));
			free(loaded_info, M_GCOV);
			return;
		}
	}
	/* Overwrite previous array. */
	free(node->loaded_info, M_GCOV);
	node->loaded_info = loaded_info;
	node->num_loaded = num + 1;
}