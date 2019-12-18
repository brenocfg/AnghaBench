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
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 

__attribute__((used)) static void
parse_dir_ask_printenv(const char *var)
{
	char *val;

	val = kern_getenv(var);
	if (val != NULL) {
		printf("  %s=%s\n", var, val);
		freeenv(val);
	}
}