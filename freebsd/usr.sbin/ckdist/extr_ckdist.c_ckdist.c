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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DISTINF 129 
#define  DISTMD5 128 
 int EOF ; 
 int /*<<< orphan*/  E_UNKNOWN ; 
 int chkinf (int /*<<< orphan*/ *,char const*) ; 
 int chkmd5 (int /*<<< orphan*/ *,char const*) ; 
 int distfile (char const*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int fail (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isstdin (char const*) ; 
 int report (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
ckdist(const char *path, int type)
{
    FILE *fp;
    int rval, c;

    if (isstdin(path)) {
	path = "(stdin)";
	fp = stdin;
    } else if ((fp = fopen(path, "r")) == NULL)
	return fail(path, NULL);
    if (!type) {
	if (fp != stdin)
	    type = distfile(path);
	if (!type)
	    if ((c = fgetc(fp)) != EOF) {
		type = c == 'M' ? DISTMD5 : c == 'P' ? DISTINF : 0;
		(void)ungetc(c, fp);
	    }
    }
    switch (type) {
    case DISTMD5:
	rval = chkmd5(fp, path);
	break;
    case DISTINF:
	rval = chkinf(fp, path);
	break;
    default:
	rval = report(path, NULL, E_UNKNOWN);
    }
    if (ferror(fp))
	warn("%s", path);
    if (fp != stdin && fclose(fp))
	err(2, "%s", path);
    return rval;
}