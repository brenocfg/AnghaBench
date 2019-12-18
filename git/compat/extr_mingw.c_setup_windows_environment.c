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
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  convert_slashes (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ is_directory (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

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

	/* calculate HOME if not set */
	if (!getenv("HOME")) {
		/*
		 * try $HOMEDRIVE$HOMEPATH - the home share may be a network
		 * location, thus also check if the path exists (i.e. is not
		 * disconnected)
		 */
		if ((tmp = getenv("HOMEDRIVE"))) {
			struct strbuf buf = STRBUF_INIT;
			strbuf_addstr(&buf, tmp);
			if ((tmp = getenv("HOMEPATH"))) {
				strbuf_addstr(&buf, tmp);
				if (is_directory(buf.buf))
					setenv("HOME", buf.buf, 1);
				else
					tmp = NULL; /* use $USERPROFILE */
			}
			strbuf_release(&buf);
		}
		/* use $USERPROFILE if the home share is not available */
		if (!tmp && (tmp = getenv("USERPROFILE")))
			setenv("HOME", tmp, 1);
	}
}