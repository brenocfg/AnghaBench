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
 scalar_t__ any (int,char*) ; 

__attribute__((used)) static int
anyof(char *s1, char *s2)
{
	int c;

	while ((c = *s1++))
		if (any(c, s2))
			return(1);
	return(0);
}