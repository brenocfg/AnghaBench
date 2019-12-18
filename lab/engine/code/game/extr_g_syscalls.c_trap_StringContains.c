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
 int /*<<< orphan*/  BOTLIB_AI_STRING_CONTAINS ; 
 int syscall (int /*<<< orphan*/ ,char*,char*,int) ; 

int trap_StringContains(char *str1, char *str2, int casesensitive) {
	return syscall( BOTLIB_AI_STRING_CONTAINS, str1, str2, casesensitive );
}