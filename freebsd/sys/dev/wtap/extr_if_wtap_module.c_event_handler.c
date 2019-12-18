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
struct wtap_plugin {int dummy; } ;
struct wtap_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; struct wtap_hal* wp_hal; } ;
struct visibility_plugin {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_WTAP ; 
 int /*<<< orphan*/  M_WTAP_PLUGIN ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  bzero (struct wtap_hal*,int) ; 
 int /*<<< orphan*/  deinit_hal (struct wtap_hal*) ; 
 int /*<<< orphan*/  deregister_plugin (struct wtap_hal*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct wtap_hal*,int /*<<< orphan*/ ) ; 
 struct wtap_hal* hal ; 
 int /*<<< orphan*/  init_hal (struct wtap_hal*) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  register_plugin (struct wtap_hal*,struct wtap_plugin*) ; 
 int /*<<< orphan*/  sdev ; 
 int /*<<< orphan*/  visibility_deinit ; 
 int /*<<< orphan*/  visibility_init ; 
 int /*<<< orphan*/  visibility_work ; 
 int /*<<< orphan*/  wtap_cdevsw ; 

__attribute__((used)) static int
event_handler(module_t module, int event, void *arg) 
{
	struct visibility_plugin *plugin;
	int e = 0; /* Error, 0 for normal return status */

	switch (event) {
	case MOD_LOAD:
		sdev = make_dev(&wtap_cdevsw,0,UID_ROOT,
		    GID_WHEEL,0600,(const char *)"wtapctl");
		hal = (struct wtap_hal *)malloc(sizeof(struct wtap_hal),
		    M_WTAP, M_NOWAIT | M_ZERO);
		bzero(hal, sizeof(struct wtap_hal));

		init_hal(hal);

		/* Setting up a simple plugin */
		plugin = (struct visibility_plugin *)malloc
		    (sizeof(struct visibility_plugin), M_WTAP_PLUGIN,
		    M_NOWAIT | M_ZERO);
		plugin->base.wp_hal  = hal;
		plugin->base.init = visibility_init;
		plugin->base.deinit = visibility_deinit;
		plugin->base.work = visibility_work;
		register_plugin(hal, (struct wtap_plugin *)plugin);

                printf("Loaded wtap wireless simulator\n");
                break;
	case MOD_UNLOAD:
		destroy_dev(sdev);
		deregister_plugin(hal);
		deinit_hal(hal);
		free(hal, M_WTAP);
		printf("Unloading wtap wireless simulator\n");
		break;
	default:
		e = EOPNOTSUPP; /* Error, Operation Not Supported */
		break;
	}

	return(e);
}