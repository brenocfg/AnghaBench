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
typedef  int /*<<< orphan*/ * hx509_env ;

/* Variables and functions */
 int /*<<< orphan*/  env_free (int /*<<< orphan*/ *) ; 

void
hx509_env_free(hx509_env *env)
{
    if (*env)
	env_free(*env);
    *env = NULL;
}