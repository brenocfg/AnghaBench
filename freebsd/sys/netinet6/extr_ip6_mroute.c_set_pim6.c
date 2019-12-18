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
 int EINVAL ; 
 int V_pim6 ; 

__attribute__((used)) static int
set_pim6(int *i)
{
	if ((*i != 1) && (*i != 0))
		return (EINVAL);

	V_pim6 = *i;

	return (0);
}