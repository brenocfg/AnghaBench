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
 int /*<<< orphan*/  asprintf (char**,char*,char const*,char const*) ; 
 char** env ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  extend_env (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int num_env ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

void
add_env(const char *var, const char *value)
{
    int i;
    char *str;
    asprintf(&str, "%s=%s", var, value);
    if(str == NULL)
	errx(1, "Out of memory!");
    for(i = 0; i < num_env; i++)
	if(strncmp(env[i], var, strlen(var)) == 0 &&
	   env[i][strlen(var)] == '='){
	    free(env[i]);
	    env[i] = str;
	    return;
	}

    extend_env(str);
}