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
 int /*<<< orphan*/  cfag12864b_setcontrollers (int,int) ; 

__attribute__((used)) static void cfag12864b_controller(unsigned char which)
{
	if (which == 0)
		cfag12864b_setcontrollers(1, 0);
	else if (which == 1)
		cfag12864b_setcontrollers(0, 1);
}