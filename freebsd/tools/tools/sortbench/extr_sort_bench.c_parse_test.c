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
typedef  enum test { ____Placeholder_test } test ;

/* Variables and functions */
 int INVALID_TEST ; 
 int PART ; 
 int RAND ; 
 int REV ; 
 int SORT ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum test
parse_test(char *test)
{
	if (strcmp(test, "rand") == 0)
		return RAND;
	else if (strcmp(test, "sort") == 0)
		return SORT;
	else if (strcmp(test, "part") == 0)
		return PART;
	else if (strcmp(test, "rev") == 0)
		return REV;
	else
		return INVALID_TEST;
}