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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ ENOTCAPABLE ; 
 int PW_CHANGE ; 
 int PW_CLASS ; 
 int PW_DIR ; 
 int PW_EXPIRE ; 
 int PW_GECOS ; 
 int PW_GID ; 
 int PW_NAME ; 
 int PW_PASSWD ; 
 int PW_SHELL ; 
 int PW_UID ; 
 int /*<<< orphan*/ * cap_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int cap_pwd_limit_fields (int /*<<< orphan*/ *,char const**,int) ; 
 scalar_t__ errno ; 
 int runtest_fields (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
test_fields(cap_channel_t *origcappwd)
{
	cap_channel_t *cappwd;
	const char *fields[10];

	/* No limits. */

	CHECK(runtest_fields(origcappwd, PW_NAME | PW_PASSWD | PW_UID |
	    PW_GID | PW_CHANGE | PW_CLASS | PW_GECOS | PW_DIR | PW_SHELL |
	    PW_EXPIRE));

	/*
	 * Allow:
	 * fields: pw_name, pw_passwd, pw_uid, pw_gid, pw_change, pw_class,
	 *         pw_gecos, pw_dir, pw_shell, pw_expire
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_name";
	fields[1] = "pw_passwd";
	fields[2] = "pw_uid";
	fields[3] = "pw_gid";
	fields[4] = "pw_change";
	fields[5] = "pw_class";
	fields[6] = "pw_gecos";
	fields[7] = "pw_dir";
	fields[8] = "pw_shell";
	fields[9] = "pw_expire";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 10) == 0);

	CHECK(runtest_fields(origcappwd, PW_NAME | PW_PASSWD | PW_UID |
	    PW_GID | PW_CHANGE | PW_CLASS | PW_GECOS | PW_DIR | PW_SHELL |
	    PW_EXPIRE));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_name, pw_passwd, pw_uid, pw_gid, pw_change
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_name";
	fields[1] = "pw_passwd";
	fields[2] = "pw_uid";
	fields[3] = "pw_gid";
	fields[4] = "pw_change";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 5) == 0);
	fields[5] = "pw_class";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 6) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_class";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_NAME | PW_PASSWD | PW_UID |
	    PW_GID | PW_CHANGE));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_class, pw_gecos, pw_dir, pw_shell, pw_expire
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_class";
	fields[1] = "pw_gecos";
	fields[2] = "pw_dir";
	fields[3] = "pw_shell";
	fields[4] = "pw_expire";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 5) == 0);
	fields[5] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 6) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_CLASS | PW_GECOS | PW_DIR |
	    PW_SHELL | PW_EXPIRE));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_name, pw_uid, pw_change, pw_gecos, pw_shell
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_name";
	fields[1] = "pw_uid";
	fields[2] = "pw_change";
	fields[3] = "pw_gecos";
	fields[4] = "pw_shell";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 5) == 0);
	fields[5] = "pw_class";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 6) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_class";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_NAME | PW_UID | PW_CHANGE |
	    PW_GECOS | PW_SHELL));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_passwd, pw_gid, pw_class, pw_dir, pw_expire
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_passwd";
	fields[1] = "pw_gid";
	fields[2] = "pw_class";
	fields[3] = "pw_dir";
	fields[4] = "pw_expire";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 5) == 0);
	fields[5] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 6) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_PASSWD | PW_GID | PW_CLASS |
	    PW_DIR | PW_EXPIRE));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_uid, pw_class, pw_shell
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_uid";
	fields[1] = "pw_class";
	fields[2] = "pw_shell";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 3) == 0);
	fields[3] = "pw_change";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 4) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_change";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_UID | PW_CLASS | PW_SHELL));

	cap_close(cappwd);

	/*
	 * Allow:
	 * fields: pw_change
	 */
	cappwd = cap_clone(origcappwd);
	CHECK(cappwd != NULL);

	fields[0] = "pw_change";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == 0);
	fields[1] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 2) == -1 &&
	    errno == ENOTCAPABLE);
	fields[0] = "pw_uid";
	CHECK(cap_pwd_limit_fields(cappwd, fields, 1) == -1 &&
	    errno == ENOTCAPABLE);

	CHECK(runtest_fields(cappwd, PW_CHANGE));

	cap_close(cappwd);
}