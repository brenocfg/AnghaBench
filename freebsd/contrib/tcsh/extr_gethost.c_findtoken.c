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
 int T_NONE ; 
 int /*<<< orphan*/ ** keyword ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
findtoken(char *ptr)
{
    int i;

    if (ptr == NULL || *ptr == '\0')
	return T_NONE;

    for (i = 0; keyword[i] != NULL; i++)
	if (strcmp(keyword[i], ptr) == 0)
	    return i;

    return T_NONE;
}