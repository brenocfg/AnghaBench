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
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 

char *
sort_strdup(const char *str)
{
	char *dup;

	if ((dup = strdup(str)) == NULL)
		err(2, NULL);
	return (dup);
}