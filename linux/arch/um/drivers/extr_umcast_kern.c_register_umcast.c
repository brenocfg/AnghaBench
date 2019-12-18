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
 int /*<<< orphan*/  mcast_transport ; 
 int /*<<< orphan*/  register_transport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucast_transport ; 

__attribute__((used)) static int register_umcast(void)
{
	register_transport(&mcast_transport);
	register_transport(&ucast_transport);
	return 0;
}