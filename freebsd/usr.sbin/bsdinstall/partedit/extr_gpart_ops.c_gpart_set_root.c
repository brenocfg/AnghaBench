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
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char const*) ; 
 int /*<<< orphan*/  gpart_show_error (char*,char*,char const*) ; 

void
gpart_set_root(const char *lg_name, const char *attribute)
{
	struct gctl_req *r;
	const char *errstr;

	r = gctl_get_handle();
	gctl_ro_param(r, "class", -1, "PART");
	gctl_ro_param(r, "arg0", -1, lg_name);
	gctl_ro_param(r, "flags", -1, "C");
	gctl_ro_param(r, "verb", -1, "set");
	gctl_ro_param(r, "attrib", -1, attribute);

	errstr = gctl_issue(r);
	if (errstr != NULL && errstr[0] != '\0') 
		gpart_show_error("Error", "Error setting parameter on disk:",
		    errstr);
	gctl_free(r);
}