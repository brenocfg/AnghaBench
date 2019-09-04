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
 int git_default_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_gpg_config (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int git_am_config(const char *k, const char *v, void *cb)
{
	int status;

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;

	return git_default_config(k, v, NULL);
}