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
typedef  int /*<<< orphan*/  pam_handle_t ;
typedef  int /*<<< orphan*/  pam_facility_t ;
typedef  int /*<<< orphan*/  openpam_style_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ OPENPAM_FEATURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAM_LOG_DEBUG ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 int /*<<< orphan*/  RETURNN (int) ; 
 int /*<<< orphan*/  VERIFY_POLICY_FILE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ openpam_check_desc_owner_perms (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,char const*) ; 
 int openpam_parse_chain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
openpam_load_file(pam_handle_t *pamh,
	const char *service,
	pam_facility_t facility,
	const char *filename,
	openpam_style_t style)
{
	FILE *f;
	int ret, serrno;

	/* attempt to open the file */
	if ((f = fopen(filename, "r")) == NULL) {
		serrno = errno;
		openpam_log(errno == ENOENT ? PAM_LOG_DEBUG : PAM_LOG_ERROR,
		    "%s: %m", filename);
		errno = serrno;
		RETURNN(-1);
	} else {
		openpam_log(PAM_LOG_DEBUG, "found %s", filename);
	}

	/* verify type, ownership and permissions */
	if (OPENPAM_FEATURE(VERIFY_POLICY_FILE) &&
	    openpam_check_desc_owner_perms(filename, fileno(f)) != 0) {
		/* already logged the cause */
		serrno = errno;
		fclose(f);
		errno = serrno;
		RETURNN(-1);
	}

	/* parse the file */
	ret = openpam_parse_chain(pamh, service, facility,
	    f, filename, style);
	RETURNN(ret);
}