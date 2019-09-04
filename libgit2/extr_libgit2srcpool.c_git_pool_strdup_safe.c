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
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 char* git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 

char *git_pool_strdup_safe(git_pool *pool, const char *str)
{
	return str ? git_pool_strdup(pool, str) : NULL;
}