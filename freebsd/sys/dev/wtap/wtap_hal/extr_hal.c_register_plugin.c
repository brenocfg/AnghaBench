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
struct wtap_plugin {int /*<<< orphan*/  (* init ) (struct wtap_plugin*) ;} ;
struct wtap_hal {struct wtap_plugin* plugin; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wtap_plugin*) ; 

void
register_plugin(struct wtap_hal *hal, struct wtap_plugin *plugin)
{

	plugin->init(plugin);
	hal->plugin = plugin;
}