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
 char* cl_getenv (char const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 

bool cl_is_env_set(const char *name)
{
	char *env = cl_getenv(name);
	bool result = (env != NULL);
	git__free(env);
	return result;
}