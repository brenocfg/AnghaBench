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
 char** env ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int num_env ; 
 char** realloc (char**,int) ; 

void
extend_env(char *str)
{
    env = realloc(env, (num_env + 1) * sizeof(*env));
    if(env == NULL)
	errx(1, "Out of memory!");
    env[num_env++] = str;
}