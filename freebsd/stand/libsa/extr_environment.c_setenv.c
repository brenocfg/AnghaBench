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
 int /*<<< orphan*/  EV_VOLATILE ; 
 int /*<<< orphan*/ * env_getenv (char const*) ; 
 int env_setenv (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
setenv(const char *name, const char *value, int overwrite)
{
    /* No guarantees about state, always assume volatile */
    if (overwrite || (env_getenv(name) == NULL))
	return(env_setenv(name, EV_VOLATILE, value, NULL, NULL));
    return(0);
}