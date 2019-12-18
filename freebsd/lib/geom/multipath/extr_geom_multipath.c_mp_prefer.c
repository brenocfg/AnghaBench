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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
mp_prefer(struct gctl_req *req)
{
	const char *name, *comp, *errstr;
	int nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs != 2) {
		gctl_error(req, "Usage: prefer GEOM PROVIDER");
		return;
	}
	name = gctl_get_ascii(req, "arg0");
	comp = gctl_get_ascii(req, "arg1");
	errstr = gctl_issue (req);
	if (errstr != NULL) {
		fprintf(stderr, "Can't set %s preferred provider to %s: %s.\n",
		    name, comp, errstr);
	}
}