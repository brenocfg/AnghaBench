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
typedef  int n_long ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static char *
number(char *s, n_long *n)
{
	for (*n = 0; isdigit(*s); s++)
		*n = (*n * 10) + *s - '0';
	return s;
}