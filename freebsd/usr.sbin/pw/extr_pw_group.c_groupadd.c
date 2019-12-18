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
typedef  int /*<<< orphan*/  uintmax_t ;
struct userconf {int dummy; } ;
struct group {char* member_0; char* member_1; int member_2; char* gr_passwd; scalar_t__ gr_gid; int /*<<< orphan*/  gr_name; int /*<<< orphan*/ * gr_mem; int /*<<< orphan*/ * member_3; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  M_ADD ; 
 int /*<<< orphan*/  W_GROUP ; 
 int addgrent (struct group*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gr_gidpolicy (struct userconf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grp_add_members (struct group**,char*) ; 
 int /*<<< orphan*/  grp_set_passwd (struct group*,int,int,int) ; 
 int print_group (struct group*,int) ; 
 int /*<<< orphan*/  pw_checkname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
groupadd(struct userconf *cnf, char *name, gid_t id, char *members, int fd,
    bool dryrun, bool pretty, bool precrypted)
{
	struct group *grp;
	int rc;

	struct group fakegroup = {
		"nogroup",
		"*",
		-1,
		NULL
	};

	grp = &fakegroup;
	grp->gr_name = pw_checkname(name, 0);
	grp->gr_passwd = "*";
	grp->gr_gid = gr_gidpolicy(cnf, id);
	grp->gr_mem = NULL;

	/*
	 * This allows us to set a group password Group passwords is an
	 * antique idea, rarely used and insecure (no secure database) Should
	 * be discouraged, but it is apparently still supported by some
	 * software.
	 */
	grp_set_passwd(grp, false, fd, precrypted);
	grp_add_members(&grp, members);
	if (dryrun)
		return (print_group(grp, pretty));

	if ((rc = addgrent(grp)) != 0) {
		if (rc == -1)
			errx(EX_IOERR, "group '%s' already exists",
			    grp->gr_name);
		else
			err(EX_IOERR, "group update");
	}

	pw_log(cnf, M_ADD, W_GROUP, "%s(%ju)", grp->gr_name,
	    (uintmax_t)grp->gr_gid);

	return (EXIT_SUCCESS);
}