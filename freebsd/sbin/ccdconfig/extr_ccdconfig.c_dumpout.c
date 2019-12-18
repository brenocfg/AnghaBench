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
typedef  int /*<<< orphan*/  unit ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int /*<<< orphan*/  gctl_rw_param (struct gctl_req*,char*,int,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
dumpout(int unit)
{
	static int v;
	struct gctl_req *grq;
	int ncp;
	char *cp;
	char const *errstr;

	grq = gctl_get_handle();
	ncp = 65536;
	cp = malloc(ncp);
	gctl_ro_param(grq, "verb", -1, "list");
	gctl_ro_param(grq, "class", -1, "CCD");
	gctl_ro_param(grq, "unit", sizeof(unit), &unit);
	gctl_rw_param(grq, "output", ncp, cp);
	errstr = gctl_issue(grq);
	if (errstr != NULL)
		errx(1, "%s\nor possibly kernel and ccdconfig out of sync",
			errstr);
	if (strlen(cp) == 0)
		errx(1, "ccd%d not configured", unit);
	if (verbose && !v) {
		printf("# ccd\t\tileave\tflags\tcomponent devices\n");
		v = 1;
	}
	printf("%s", cp);
	free(cp);
	return (0);
}