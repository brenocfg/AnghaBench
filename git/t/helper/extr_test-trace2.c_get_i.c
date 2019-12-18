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
 scalar_t__ ERANGE ; 
 int MyError ; 
 int MyOk ; 
 scalar_t__ errno ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static int get_i(int *p_value, const char *data)
{
	char *endptr;

	if (!data || !*data)
		return MyError;

	*p_value = strtol(data, &endptr, 10);
	if (*endptr || errno == ERANGE)
		return MyError;

	return MyOk;
}