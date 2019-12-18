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
struct xpasswd {int pw_selected; int pw_uid; char* pw_passwd; int /*<<< orphan*/  pw_name; } ;
struct xgroup {scalar_t__ gr_mem; int /*<<< orphan*/  gr_name; } ;

/* Variables and functions */
 scalar_t__ d_flag ; 
 scalar_t__ everything ; 
 scalar_t__ g_args ; 
 struct xgroup* grps ; 
 scalar_t__ l_args ; 
 scalar_t__ member (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int ngrps ; 
 unsigned int npwds ; 
 scalar_t__ p_flag ; 
 struct xpasswd* pwds ; 
 scalar_t__ s_flag ; 
 scalar_t__ u_flag ; 

__attribute__((used)) static void
select_users(void)
{
	unsigned int i, j;
	struct xgroup *grp;
	struct xpasswd *pwd;

	for (i = 0, pwd = pwds; i < npwds; ++i, ++pwd) {
		if (everything) {
			pwd->pw_selected = 1;
			continue;
		}
		if (d_flag)
			if ((i > 0 && pwd->pw_uid == pwd[-1].pw_uid) ||
			    (i < npwds - 1 && pwd->pw_uid == pwd[1].pw_uid)) {
				pwd->pw_selected = 1;
				continue;
			}
		if (g_args) {
			for (j = 0, grp = grps; j < ngrps; ++j, ++grp) {
				if (member(grp->gr_name, g_args) &&
				    member(pwd->pw_name, grp->gr_mem)) {
					pwd->pw_selected = 1;
					break;
				}
			}
			if (pwd->pw_selected)
				continue;
		}
		if (l_args)
			if (member(pwd->pw_name, l_args)) {
				pwd->pw_selected = 1;
				continue;
			}
		if (p_flag)
			if (pwd->pw_passwd[0] == '\0') {
				pwd->pw_selected = 1;
				continue;
			}
		if (s_flag)
			if (pwd->pw_uid < 1000 || pwd->pw_uid == 65534) {
				pwd->pw_selected = 1;
				continue;
			}
		if (u_flag)
			if (pwd->pw_uid >= 1000 && pwd->pw_uid != 65534) {
				pwd->pw_selected = 1;
				continue;
			}
	}
}