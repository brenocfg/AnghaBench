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
struct wtap_hal {TYPE_1__* plugin; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
deregister_plugin(struct wtap_hal *hal)
{

	hal->plugin->deinit(hal->plugin);
	hal->plugin = NULL; /* catch illegal usages */
}