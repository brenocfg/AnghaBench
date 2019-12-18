#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gctl_req {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  defaultno; } ;
struct TYPE_3__ {int bootcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* GPART_FLAGS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bootcode_path (char const*) ; 
 char* choose_part_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_scheme () ; 
 TYPE_2__ dialog_vars ; 
 int dialog_yesno (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char const*) ; 
 TYPE_1__* get_part_metadata (char const*,int) ; 
 int /*<<< orphan*/  gpart_show_error (char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  is_scheme_bootable (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

int
gpart_partition(const char *lg_name, const char *scheme)
{
	int cancel;
	struct gctl_req *r;
	const char *errstr;

schememenu:
	if (scheme == NULL) {
		scheme = choose_part_type(default_scheme());

		if (scheme == NULL)
			return (-1);

		if (!is_scheme_bootable(scheme)) {
			char message[512];
			sprintf(message, "This partition scheme (%s) is not "
			    "bootable on this platform. Are you sure you want "
			    "to proceed?", scheme);
			dialog_vars.defaultno = TRUE;
			cancel = dialog_yesno("Warning", message, 0, 0);
			dialog_vars.defaultno = FALSE;
			if (cancel) { /* cancel */
				/* Reset scheme so user can choose another */
				scheme = NULL;
				goto schememenu;
			}
		}
	}

	r = gctl_get_handle();
	gctl_ro_param(r, "class", -1, "PART");
	gctl_ro_param(r, "arg0", -1, lg_name);
	gctl_ro_param(r, "flags", -1, GPART_FLAGS);
	gctl_ro_param(r, "scheme", -1, scheme);
	gctl_ro_param(r, "verb", -1, "create");

	errstr = gctl_issue(r);
	if (errstr != NULL && errstr[0] != '\0') {
		gpart_show_error("Error", NULL, errstr);
		gctl_free(r);
		scheme = NULL;
		goto schememenu;
	}
	gctl_free(r);

	if (bootcode_path(scheme) != NULL)
		get_part_metadata(lg_name, 1)->bootcode = 1;
	return (0);
}