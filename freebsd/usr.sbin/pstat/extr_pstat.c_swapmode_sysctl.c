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
struct xswdev {scalar_t__ xsw_version; scalar_t__ xsw_dev; int /*<<< orphan*/  xsw_flags; int /*<<< orphan*/  xsw_nblks; int /*<<< orphan*/  xsw_used; } ;
struct kvm_swap {int /*<<< orphan*/  ksw_flags; int /*<<< orphan*/  ksw_total; int /*<<< orphan*/  ksw_used; int /*<<< orphan*/  ksw_devname; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ NODEV ; 
 int /*<<< orphan*/  S_IFCHR ; 
 scalar_t__ XSWDEV_VERSION ; 
 char* devname (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  print_swap (struct kvm_swap*) ; 
 int /*<<< orphan*/  print_swap_header () ; 
 int /*<<< orphan*/  print_swap_total () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int sysctl (int*,size_t,struct xswdev*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysctlnametomib (char*,int*,size_t*) ; 

__attribute__((used)) static void
swapmode_sysctl(void)
{
	struct kvm_swap ksw;
	struct xswdev xsw;
	size_t mibsize, size;
	int mib[16], n;

	print_swap_header();
	mibsize = sizeof mib / sizeof mib[0];
	if (sysctlnametomib("vm.swap_info", mib, &mibsize) == -1)
		err(1, "sysctlnametomib()");
	for (n = 0; ; ++n) {
		mib[mibsize] = n;
		size = sizeof xsw;
		if (sysctl(mib, mibsize + 1, &xsw, &size, NULL, 0) == -1)
			break;
		if (xsw.xsw_version != XSWDEV_VERSION)
			errx(1, "xswdev version mismatch");
		if (xsw.xsw_dev == NODEV)
			snprintf(ksw.ksw_devname, sizeof ksw.ksw_devname,
			    "<NFSfile>");
		else
			snprintf(ksw.ksw_devname, sizeof ksw.ksw_devname,
			    "/dev/%s", devname(xsw.xsw_dev, S_IFCHR));
		ksw.ksw_used = xsw.xsw_used;
		ksw.ksw_total = xsw.xsw_nblks;
		ksw.ksw_flags = xsw.xsw_flags;
		print_swap(&ksw);
	}
	if (errno != ENOENT)
		err(1, "sysctl()");
	print_swap_total();
}