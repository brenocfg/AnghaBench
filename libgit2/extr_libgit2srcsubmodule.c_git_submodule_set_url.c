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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int write_var (int /*<<< orphan*/ *,char const*,char*,char const*) ; 

int git_submodule_set_url(git_repository *repo, const char *name, const char *url)
{
	assert(repo && name && url);

	return write_var(repo, name, "url", url);
}