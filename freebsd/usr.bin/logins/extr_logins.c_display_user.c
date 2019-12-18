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
struct xpasswd {scalar_t__ pw_gid; scalar_t__ pw_expire; scalar_t__ pw_change; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_gecos; scalar_t__ pw_uid; } ;
struct xgroup {char* gr_name; scalar_t__ gr_gid; int /*<<< orphan*/  gr_mem; } ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ebuf ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 scalar_t__ a_flag ; 
 struct xgroup* find_group_bygid (scalar_t__) ; 
 struct tm* gmtime (scalar_t__*) ; 
 struct xgroup* grps ; 
 scalar_t__ m_flag ; 
 int /*<<< orphan*/  member (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ngrps ; 
 scalar_t__ o_flag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 scalar_t__ x_flag ; 

__attribute__((used)) static void
display_user(struct xpasswd *pwd)
{
	struct xgroup *grp;
	unsigned int i;
	char cbuf[16], ebuf[16];
	struct tm *tm;

	grp = find_group_bygid(pwd->pw_gid);
	printf(o_flag ? "%s:%ld:%s:%ld:%s" : "%-15s %-7ld %-15s %-7ld %s\n",
	    pwd->pw_name, (long)pwd->pw_uid, grp ? grp->gr_name : "",
	    (long)pwd->pw_gid, pwd->pw_gecos);
	if (m_flag) {
		for (i = 0, grp = grps; i < ngrps; ++i, ++grp) {
			if (grp->gr_gid == pwd->pw_gid ||
			    !member(pwd->pw_name, grp->gr_mem))
				continue;
			printf(o_flag ? "%s:%s:%ld" : "%24s%-15s %-7ld\n",
			    "", grp->gr_name, (long)grp->gr_gid);
		}
	}
	if (x_flag) {
		printf(o_flag ? "%s:%s" : "%24s%s\n", "", pwd->pw_dir);
		printf(o_flag ? "%s:%s" : "%24s%s\n", "", pwd->pw_shell);
	}
	if (a_flag) {
		tm = gmtime(&pwd->pw_change);
		strftime(cbuf, sizeof(cbuf), pwd->pw_change ? "%F" : "0", tm);
		tm = gmtime(&pwd->pw_expire);
		strftime(ebuf, sizeof(ebuf), pwd->pw_expire ? "%F" : "0", tm);
		printf(o_flag ? "%s:%s:%s" : "%24s%s %s\n", "", cbuf, ebuf);
	}
	if (o_flag)
		printf("\n");
}