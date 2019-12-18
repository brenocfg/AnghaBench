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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  R_CURSOR ; 
 int /*<<< orphan*/  R_FIRST ; 
 int /*<<< orphan*/  R_IAFTER ; 
 int /*<<< orphan*/  R_IBEFORE ; 
 int /*<<< orphan*/  R_LAST ; 
 int /*<<< orphan*/  R_NEXT ; 
 int /*<<< orphan*/  R_NOOVERWRITE ; 
 int /*<<< orphan*/  R_PREV ; 
 int /*<<< orphan*/  R_SETCURSOR ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  lineno ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static u_int
setflags(char *s)
{
	char *p;

	for (; isspace((unsigned char)*s); ++s);
	if (*s == '\n' || *s == '\0')
		return 0;
	if ((p = strchr(s, '\n')) != NULL)
		*p = '\0';
	if (!strcmp(s, "R_CURSOR"))		return R_CURSOR;
	if (!strcmp(s, "R_FIRST"))		return R_FIRST;
	if (!strcmp(s, "R_IAFTER")) 		return R_IAFTER;
	if (!strcmp(s, "R_IBEFORE")) 		return R_IBEFORE;
	if (!strcmp(s, "R_LAST")) 		return R_LAST;
	if (!strcmp(s, "R_NEXT")) 		return R_NEXT;
	if (!strcmp(s, "R_NOOVERWRITE"))	return R_NOOVERWRITE;
	if (!strcmp(s, "R_PREV"))		return R_PREV;
	if (!strcmp(s, "R_SETCURSOR"))		return R_SETCURSOR;

	errx(1, "line %zu: %s: unknown flag", lineno, s);
	/* NOTREACHED */
}