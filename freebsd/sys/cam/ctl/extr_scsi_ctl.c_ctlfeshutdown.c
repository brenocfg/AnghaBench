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
 int /*<<< orphan*/  ctlfe_driver ; 
 int /*<<< orphan*/  ctlfe_list_mtx ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int periphdriver_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctlfeshutdown(void)
{
	int error;

	error = periphdriver_unregister(&ctlfe_driver);
	if (error != 0)
		return (error);
	mtx_destroy(&ctlfe_list_mtx);
	return (0);
}