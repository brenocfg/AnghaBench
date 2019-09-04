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
 int /*<<< orphan*/  GIT_LOCALE_PATH ; 
 int /*<<< orphan*/  GIT_TEXT_DOMAIN_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  bindtextdomain (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_gettext_charset (char*) ; 
 int /*<<< orphan*/  is_directory (char const*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 char* system_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textdomain (char*) ; 
 int /*<<< orphan*/  use_gettext_poison () ; 

void git_setup_gettext(void)
{
	const char *podir = getenv(GIT_TEXT_DOMAIN_DIR_ENVIRONMENT);
	char *p = NULL;

	if (!podir)
		podir = p = system_path(GIT_LOCALE_PATH);

	use_gettext_poison(); /* getenv() reentrancy paranoia */

	if (!is_directory(podir)) {
		free(p);
		return;
	}

	bindtextdomain("git", podir);
	setlocale(LC_MESSAGES, "");
	setlocale(LC_TIME, "");
	init_gettext_charset("git");
	textdomain("git");

	free(p);
}