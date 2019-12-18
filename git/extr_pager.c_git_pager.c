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
 char* DEFAULT_PAGER ; 
 int /*<<< orphan*/  core_pager_config ; 
 char* getenv (char*) ; 
 char* pager_program ; 
 int /*<<< orphan*/  read_early_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

const char *git_pager(int stdout_is_tty)
{
	const char *pager;

	if (!stdout_is_tty)
		return NULL;

	pager = getenv("GIT_PAGER");
	if (!pager) {
		if (!pager_program)
			read_early_config(core_pager_config, NULL);
		pager = pager_program;
	}
	if (!pager)
		pager = getenv("PAGER");
	if (!pager)
		pager = DEFAULT_PAGER;
	if (!*pager || !strcmp(pager, "cat"))
		pager = NULL;

	return pager;
}