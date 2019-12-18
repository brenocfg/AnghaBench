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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  au_mask_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  _IONBF ; 
 scalar_t__ atf_utils_file_exists (char*) ; 
 int /*<<< orphan*/  check_audit_startup (struct pollfd*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  get_audit_mask (char const*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_preselect_mode (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system (char*) ; 

FILE
*setup(struct pollfd fd[], const char *name)
{
	au_mask_t fmask, nomask;
	fmask = get_audit_mask(name);
	nomask = get_audit_mask("no");
	FILE *pipestream;

	ATF_REQUIRE((fd[0].fd = open("/dev/auditpipe", O_RDONLY)) != -1);
	ATF_REQUIRE((pipestream = fdopen(fd[0].fd, "r")) != NULL);
	fd[0].events = POLLIN;

	/*
	 * Disable stream buffering for read operations from /dev/auditpipe.
	 * Otherwise it is possible that fread(3), called via au_read_rec(3),
	 * can store buffered data in user-space unbeknown to ppoll(2), which
	 * as a result, reports that /dev/auditpipe is empty.
	 */
	ATF_REQUIRE_EQ(0, setvbuf(pipestream, NULL, _IONBF, 0));

	/* Set local preselection audit_class as "no" for audit startup */
	set_preselect_mode(fd[0].fd, &nomask);
	ATF_REQUIRE_EQ(0, system("service auditd onestatus || \
	{ service auditd onestart && touch started_auditd ; }"));

	/* If 'started_auditd' exists, that means we started auditd(8) */
	if (atf_utils_file_exists("started_auditd"))
		check_audit_startup(fd, "audit startup", pipestream);

	/* Set local preselection parameters specific to "name" audit_class */
	set_preselect_mode(fd[0].fd, &fmask);
	return (pipestream);
}