#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {char* pw_name; char* pw_passwd; char* pw_gecos; char* pw_class; char* pw_dir; char* pw_shell; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  fake ;
struct TYPE_2__ {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct passwd*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* privsep_pw ; 

struct passwd *
fakepw(void)
{
	static struct passwd fake;

	memset(&fake, 0, sizeof(fake));
	fake.pw_name = "NOUSER";
	fake.pw_passwd =
	    "$2a$06$r3.juUaHZDlIbQaO2dS9FuYxL1W9M81R1Tc92PoSNmzvpEqLkLGrK";
#ifdef HAVE_STRUCT_PASSWD_PW_GECOS
	fake.pw_gecos = "NOUSER";
#endif
	fake.pw_uid = privsep_pw == NULL ? (uid_t)-1 : privsep_pw->pw_uid;
	fake.pw_gid = privsep_pw == NULL ? (gid_t)-1 : privsep_pw->pw_gid;
#ifdef HAVE_STRUCT_PASSWD_PW_CLASS
	fake.pw_class = "";
#endif
	fake.pw_dir = "/nonexist";
	fake.pw_shell = "/nonexist";

	return (&fake);
}