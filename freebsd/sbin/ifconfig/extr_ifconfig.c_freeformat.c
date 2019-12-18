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
 int /*<<< orphan*/ * f_addr ; 
 int /*<<< orphan*/ * f_ether ; 
 int /*<<< orphan*/ * f_inet ; 
 int /*<<< orphan*/ * f_inet6 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void freeformat(void)
{

	if (f_inet != NULL)
		free(f_inet);
	if (f_inet6 != NULL)
		free(f_inet6);
	if (f_ether != NULL)
		free(f_ether);
	if (f_addr != NULL)
		free(f_addr);
}