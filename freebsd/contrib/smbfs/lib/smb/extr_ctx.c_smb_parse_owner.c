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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  endpwent () ; 
 struct group* getgrnam (char*) ; 
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
smb_parse_owner(char *pair, uid_t *uid, gid_t *gid)
{
	struct group *gr;
	struct passwd *pw;
	char *cp;

	cp = strchr(pair, ':');
	if (cp) {
		*cp++ = '\0';
		if (*cp) {
			gr = getgrnam(cp);
			if (gr) {
				*gid = gr->gr_gid;
			} else
				smb_error("Invalid group name %s, ignored",
				    0, cp);
		}
	}
	if (*pair) {
		pw = getpwnam(pair);
		if (pw) {
			*uid = pw->pw_uid;
		} else
			smb_error("Invalid user name %s, ignored", 0, pair);
	}
	endpwent();
	return 0;
}