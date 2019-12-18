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
 int update_unit (int,unsigned int) ; 

__attribute__((used)) static int
update_unit_approx (int in, unsigned mult)
{
    if (in / mult > 0)
	return 0;
    else
	return update_unit (in, mult);
}