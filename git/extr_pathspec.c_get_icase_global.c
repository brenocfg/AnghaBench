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
 int /*<<< orphan*/  GIT_ICASE_PATHSPECS_ENVIRONMENT ; 
 int git_env_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_icase_global(void)
{
	static int icase = -1;

	if (icase < 0)
		icase = git_env_bool(GIT_ICASE_PATHSPECS_ENVIRONMENT, 0);

	return icase;
}