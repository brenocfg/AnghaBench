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
typedef  int /*<<< orphan*/  longname ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ test (char*,unsigned int) ; 

int
main(int argc, char **argv)
{
    FILE *f;
    char buf[1024];
    char filename[256] = "NormalizationTest.txt";
    unsigned failures = 0;
    unsigned lineno = 0;

    if (argc > 2)
	errx(1, "usage: %s [file]", argv[0]);
    else if (argc == 2)
	strlcpy(filename, argv[1], sizeof(filename));

    f = fopen(filename, "r");
    if (f == NULL) {
	const char *srcdir = getenv("srcdir");
	if (srcdir != NULL) {
	    char longname[256];
	    snprintf(longname, sizeof(longname), "%s/%s", srcdir, filename);
	    f = fopen(longname, "r");
	}
	if (f == NULL)
	    err(1, "open %s", filename);
    }
    while (fgets(buf, sizeof(buf), f) != NULL) {
	lineno++;
	if (buf[0] == '#')
	    continue;
	if (buf[0] == '@') {
	    continue;
	}
	failures += test(buf, lineno);
    }
    fclose(f);
    return failures != 0;
}