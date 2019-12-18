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
typedef  scalar_t__ uid_t ;
struct passwd {char* pw_name; char* pw_passwd; char* pw_class; char* pw_gecos; char* pw_dir; char* pw_shell; scalar_t__ pw_gid; scalar_t__ pw_uid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct passwd*,int /*<<< orphan*/ ,int) ; 

void
__pw_initpwd(struct passwd *pwd)
{
	static char nul[] = "";

	memset(pwd, 0, sizeof(*pwd));
	pwd->pw_uid = (uid_t)-1;  /* Considered least likely to lead to */
	pwd->pw_gid = (gid_t)-1;  /* a security issue.                  */
	pwd->pw_name = nul;
	pwd->pw_passwd = nul;
	pwd->pw_class = nul;
	pwd->pw_gecos = nul;
	pwd->pw_dir = nul;
	pwd->pw_shell = nul;
}