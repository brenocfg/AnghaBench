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
 scalar_t__ LS_HASH ; 
 scalar_t__ LS_START ; 
 int /*<<< orphan*/  MAXLINE ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  input ; 
 int /*<<< orphan*/  linenum ; 
 scalar_t__ linestate ; 
 char const* skipcomment (char const*) ; 
 char const* skipline (char const*) ; 
 char const* tline ; 

__attribute__((used)) static const char *
skiphash(void)
{
	const char *cp;

	linenum++;
	if (fgets(tline, MAXLINE, input) == NULL) {
		if (ferror(input))
			err(2, "can't read %s", filename);
		else
			return (NULL);
	}
	cp = skipcomment(tline);
	if (linestate == LS_START && *cp == '#') {
		linestate = LS_HASH;
		return (skipcomment(cp + 1));
	} else if (*cp == '\0') {
		return (cp);
	} else {
		return (skipline(cp));
	}
}