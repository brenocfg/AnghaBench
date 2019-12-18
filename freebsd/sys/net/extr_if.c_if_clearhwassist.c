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
struct ifnet {scalar_t__ if_hwassist; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */

int
if_clearhwassist(if_t ifp)
{
	((struct ifnet *)ifp)->if_hwassist = 0;
	return (0);
}