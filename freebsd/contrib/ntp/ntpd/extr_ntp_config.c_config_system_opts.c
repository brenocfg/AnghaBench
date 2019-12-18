#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  disable_opts; int /*<<< orphan*/  enable_opts; } ;
typedef  TYPE_1__ config_tree ;

/* Variables and functions */
 int /*<<< orphan*/  apply_enable_disable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
config_system_opts(
	config_tree *ptree
	)
{
	apply_enable_disable(ptree->enable_opts, 1);
	apply_enable_disable(ptree->disable_opts, 0);
}