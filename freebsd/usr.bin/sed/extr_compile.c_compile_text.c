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
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EATSPACE () ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/ * cu_fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* malloc (int) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static char *
compile_text(void)
{
	int asize, esc_nl, size;
	char *text, *p, *op, *s;
	char lbuf[_POSIX2_LINE_MAX + 1];

	asize = 2 * _POSIX2_LINE_MAX + 1;
	if ((text = malloc(asize)) == NULL)
		err(1, "malloc");
	size = 0;
	while (cu_fgets(lbuf, sizeof(lbuf), NULL) != NULL) {
		op = s = text + size;
		p = lbuf;
#ifdef LEGACY_BSDSED_COMPAT
		EATSPACE();
#endif
		for (esc_nl = 0; *p != '\0'; p++) {
			if (*p == '\\' && p[1] != '\0' && *++p == '\n')
				esc_nl = 1;
			*s++ = *p;
		}
		size += s - op;
		if (!esc_nl) {
			*s = '\0';
			break;
		}
		if (asize - size < _POSIX2_LINE_MAX + 1) {
			asize *= 2;
			if ((text = realloc(text, asize)) == NULL)
				err(1, "realloc");
		}
	}
	text[size] = '\0';
	if ((p = realloc(text, size + 1)) == NULL)
		err(1, "realloc");
	return (p);
}