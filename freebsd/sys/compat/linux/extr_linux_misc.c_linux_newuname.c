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
typedef  int /*<<< orphan*/  utsname ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct linux_newuname_args {int /*<<< orphan*/  buf; } ;
struct l_new_utsname {char* sysname; char* release; char* version; char* machine; int /*<<< orphan*/  domainname; int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int LINUX_MAX_UTSNAME ; 
 int /*<<< orphan*/  bzero (struct l_new_utsname*,int) ; 
 int copyout (struct l_new_utsname*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getcreddomainname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getcredhostname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  linux_get_osname (struct thread*,char*) ; 
 int /*<<< orphan*/  linux_get_osrelease (struct thread*,char*) ; 
 char* linux_kplatform ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* version ; 

int
linux_newuname(struct thread *td, struct linux_newuname_args *args)
{
	struct l_new_utsname utsname;
	char osname[LINUX_MAX_UTSNAME];
	char osrelease[LINUX_MAX_UTSNAME];
	char *p;

	linux_get_osname(td, osname);
	linux_get_osrelease(td, osrelease);

	bzero(&utsname, sizeof(utsname));
	strlcpy(utsname.sysname, osname, LINUX_MAX_UTSNAME);
	getcredhostname(td->td_ucred, utsname.nodename, LINUX_MAX_UTSNAME);
	getcreddomainname(td->td_ucred, utsname.domainname, LINUX_MAX_UTSNAME);
	strlcpy(utsname.release, osrelease, LINUX_MAX_UTSNAME);
	strlcpy(utsname.version, version, LINUX_MAX_UTSNAME);
	for (p = utsname.version; *p != '\0'; ++p)
		if (*p == '\n') {
			*p = '\0';
			break;
		}
	strlcpy(utsname.machine, linux_kplatform, LINUX_MAX_UTSNAME);

	return (copyout(&utsname, args->buf, sizeof(utsname)));
}