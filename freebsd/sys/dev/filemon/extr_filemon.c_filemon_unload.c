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
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemon_dev ; 
 int /*<<< orphan*/  filemon_wrapper_deinstall () ; 

__attribute__((used)) static int
filemon_unload(void)
{

	destroy_dev(filemon_dev);
	filemon_wrapper_deinstall();

	return (0);
}