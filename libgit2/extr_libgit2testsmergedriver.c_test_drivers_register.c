#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_driver_register (char*,int /*<<< orphan*/ *) ; 
 TYPE_2__ test_driver_custom ; 
 TYPE_1__ test_driver_wildcard ; 

__attribute__((used)) static void test_drivers_register(void)
{
	cl_git_pass(git_merge_driver_register("custom", &test_driver_custom.base));
	cl_git_pass(git_merge_driver_register("*", &test_driver_wildcard.base));
}