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
 int /*<<< orphan*/  convert_slashes (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

__attribute__((used)) static void setup_windows_environment(void)
{
	char *tmp = getenv("TMPDIR");

	/* on Windows it is TMP and TEMP */
	if (!tmp) {
		if (!(tmp = getenv("TMP")))
			tmp = getenv("TEMP");
		if (tmp) {
			setenv("TMPDIR", tmp, 1);
			tmp = getenv("TMPDIR");
		}
	}

	if (tmp) {
		/*
		 * Convert all dir separators to forward slashes,
		 * to help shell commands called from the Git
		 * executable (by not mistaking the dir separators
		 * for escape characters).
		 */
		convert_slashes(tmp);
	}

	/* simulate TERM to enable auto-color (see color.c) */
	if (!getenv("TERM"))
		setenv("TERM", "cygwin", 1);
}