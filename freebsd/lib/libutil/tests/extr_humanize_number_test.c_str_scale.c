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
 int HN_AUTOSCALE ; 
 int HN_GETSCALE ; 
 int /*<<< orphan*/  MAX_INT_STR_DIGITS ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* str_flags (int,char*) ; 

__attribute__((used)) static char *
str_scale(int scale) {
	char *result;

	if (scale == HN_AUTOSCALE || scale == HN_GETSCALE)
		return str_flags(scale, "");

	result = malloc(MAX_INT_STR_DIGITS);
	result[0] = '\0';
	snprintf(result, MAX_INT_STR_DIGITS, "%d", scale);
	return result;
}