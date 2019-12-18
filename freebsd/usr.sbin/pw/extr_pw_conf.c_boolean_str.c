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
 int P_NO ; 
 int P_NONE ; 
 int P_RANDOM ; 
 char const** boolfalse ; 
 char const** booltrue ; 

char const     *
boolean_str(int val)
{
	if (val == P_NO)
		return (boolfalse[0]);
	else if (val == P_RANDOM)
		return ("random");
	else if (val == P_NONE)
		return ("none");
	else
		return (booltrue[0]);
}