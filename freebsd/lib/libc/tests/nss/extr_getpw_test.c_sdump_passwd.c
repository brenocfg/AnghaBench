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
struct passwd {char* pw_name; char* pw_passwd; int pw_uid; int pw_gid; int /*<<< orphan*/  pw_fields; scalar_t__ pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_class; scalar_t__ pw_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdump_passwd(struct passwd *pwd, char *buffer, size_t buflen)
{
	snprintf(buffer, buflen, "%s:%s:%d:%d:%jd:%s:%s:%s:%s:%jd:%d",
	    pwd->pw_name, pwd->pw_passwd, pwd->pw_uid, pwd->pw_gid,
	    (uintmax_t)pwd->pw_change, pwd->pw_class, pwd->pw_gecos,
	    pwd->pw_dir, pwd->pw_shell, (uintmax_t)pwd->pw_expire,
	    pwd->pw_fields);
}