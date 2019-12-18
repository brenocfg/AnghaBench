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
struct __user_cap_header_struct {scalar_t__ pid; int /*<<< orphan*/  version; } ;
struct __user_cap_data_struct {int effective; int permitted; scalar_t__ inheritable; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AID_INET ; 
 int /*<<< orphan*/  AID_KEYSTORE ; 
 int /*<<< orphan*/  AID_WIFI ; 
 int /*<<< orphan*/  ANDROID_SETGROUPS_OVERRIDE ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int CAP_NET_ADMIN ; 
 int CAP_NET_RAW ; 
 int /*<<< orphan*/  PR_SET_KEEPCAPS ; 
 int /*<<< orphan*/  _LINUX_CAPABILITY_VERSION ; 
 int /*<<< orphan*/  capset (struct __user_cap_header_struct*,struct __user_cap_data_struct*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 

int os_program_init(void)
{
#ifdef ANDROID
	/*
	 * We ignore errors here since errors are normal if we
	 * are already running as non-root.
	 */
#ifdef ANDROID_SETGROUPS_OVERRIDE
	gid_t groups[] = { ANDROID_SETGROUPS_OVERRIDE };
#else /* ANDROID_SETGROUPS_OVERRIDE */
	gid_t groups[] = { AID_INET, AID_WIFI, AID_KEYSTORE };
#endif /* ANDROID_SETGROUPS_OVERRIDE */
	struct __user_cap_header_struct header;
	struct __user_cap_data_struct cap;

	setgroups(ARRAY_SIZE(groups), groups);

	prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0);

	setgid(AID_WIFI);
	setuid(AID_WIFI);

	header.version = _LINUX_CAPABILITY_VERSION;
	header.pid = 0;
	cap.effective = cap.permitted =
		(1 << CAP_NET_ADMIN) | (1 << CAP_NET_RAW);
	cap.inheritable = 0;
	capset(&header, &cap);
#endif /* ANDROID */

	return 0;
}