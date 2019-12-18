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
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
g_label_is_name_ok(const char *label)
{
	const char *s;

	/* Check if the label starts from ../ */
	if (strncmp(label, "../", 3) == 0)
		return (0);
	/* Check if the label contains /../ */
	if (strstr(label, "/../") != NULL)
		return (0);
	/* Check if the label ends at ../ */
	if ((s = strstr(label, "/..")) != NULL && s[3] == '\0')
		return (0);
	return (1);
}