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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_shutdown ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  modules_sx ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
module_init(void *arg)
{

	sx_init(&modules_sx, "module subsystem sx lock");
	TAILQ_INIT(&modules);
	EVENTHANDLER_REGISTER(shutdown_final, module_shutdown, NULL,
	    SHUTDOWN_PRI_DEFAULT);
}