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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int atoint (char*,long*) ; 
 int hextoint (char*,int /*<<< orphan*/ *) ; 
 int octtoint (char*,int /*<<< orphan*/ *) ; 

int
decodeint(
	char *str,
	long *val
	)
{
	if (*str == '0') {
		if (*(str+1) == 'x' || *(str+1) == 'X')
		    return hextoint(str+2, (u_long *)val);
		return octtoint(str, (u_long *)val);
	}
	return atoint(str, val);
}