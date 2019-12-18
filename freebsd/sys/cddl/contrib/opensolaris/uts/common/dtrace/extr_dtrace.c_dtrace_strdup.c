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
 int /*<<< orphan*/  KM_SLEEP ; 
 char* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
dtrace_strdup(const char *str)
{
	char *new = kmem_zalloc((str != NULL ? strlen(str) : 0) + 1, KM_SLEEP);

	if (str != NULL)
		(void) strcpy(new, str);

	return (new);
}