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
 int /*<<< orphan*/  clogp ; 
 int /*<<< orphan*/  sysctl_teardown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int
k_uvm_fini(void *arg)
{

	sysctl_teardown(&clogp);

	return 0;
}