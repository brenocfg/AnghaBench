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
 scalar_t__ strncmp (char*,char*,size_t) ; 

__attribute__((used)) static int
find_var(char **env, char *assignment, size_t len)
{
    int i;
    for(i = 0; env != NULL && env[i] != NULL; i++)
	if(strncmp(env[i], assignment, len) == 0)
	    return i;
    return -1;
}