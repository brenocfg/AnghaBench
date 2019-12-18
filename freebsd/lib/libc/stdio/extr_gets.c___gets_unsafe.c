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
typedef  int /*<<< orphan*/  w ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int /*<<< orphan*/  ORIENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int __sgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _write (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  stdin ; 

char *
__gets_unsafe(char *buf)
{
	int c;
	char *s, *ret;
	static int warned;
	static const char w[] =
	    "warning: this program uses gets(), which is unsafe.\n";

	FLOCKFILE_CANCELSAFE(stdin);
	ORIENT(stdin, -1);
	if (!warned) {
		(void) _write(STDERR_FILENO, w, sizeof(w) - 1);
		warned = 1;
	}
	for (s = buf; (c = __sgetc(stdin)) != '\n'; ) {
		if (c == EOF) {
			if (s == buf) {
				ret = NULL;
				goto end;
			} else
				break;
		} else
			*s++ = c;
	}
	*s = 0;
	ret = buf;
end:
	FUNLOCKFILE_CANCELSAFE();
	return (ret);
}