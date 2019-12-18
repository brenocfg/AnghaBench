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
struct wtap_plugin {int /*<<< orphan*/  wp_sdev; } ;
struct visibility_plugin {int /*<<< orphan*/  pl_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WTAP_PLUGIN ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct visibility_plugin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
visibility_deinit(struct wtap_plugin *plugin)
{
	struct visibility_plugin *vis_plugin;

	vis_plugin = (struct visibility_plugin *) plugin;
	destroy_dev(plugin->wp_sdev);
	mtx_destroy(&vis_plugin->pl_mtx);
	free(vis_plugin, M_WTAP_PLUGIN);
	printf("Removing visibility wtap plugin...\n");
}