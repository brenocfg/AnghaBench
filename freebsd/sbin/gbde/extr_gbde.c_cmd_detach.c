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
 int BUFSIZ ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void
cmd_detach(const char *dest)
{
	struct gctl_req *r;
	const char *errstr;
	char buf[BUFSIZ];

	r = gctl_get_handle();
	gctl_ro_param(r, "verb", -1, "destroy geom");
	gctl_ro_param(r, "class", -1, "BDE");
	sprintf(buf, "%s.bde", dest);
	gctl_ro_param(r, "geom", -1, buf);
	/* gctl_dump(r, stdout); */
	errstr = gctl_issue(r);
	if (errstr != NULL)
		errx(1, "Detach of %s failed: %s", dest, errstr);
	exit (0);
}