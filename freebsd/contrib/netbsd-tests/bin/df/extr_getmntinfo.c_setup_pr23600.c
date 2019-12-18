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
struct statvfs {char* f_mntfromname; char* f_mntonname; scalar_t__ f_bresvd; scalar_t__ f_bavail; scalar_t__ f_bfree; scalar_t__ f_blocks; int /*<<< orphan*/  f_frsize; int /*<<< orphan*/  f_bsize; } ;

/* Variables and functions */
 scalar_t__ AVAIL ; 
 int /*<<< orphan*/  BSIZE ; 
 scalar_t__ TOTAL ; 
 scalar_t__ USED ; 
 struct statvfs* getnewstatvfs () ; 

__attribute__((used)) static void
setup_pr23600(void)
{
	static const struct statvfs tmpl = {
#define	BSIZE	512
#define	TOTAL	20971376ULL
#define	USED	5719864ULL
#define	AVAIL	15251512ULL
		.f_bsize = BSIZE,
		.f_frsize = BSIZE,
		.f_blocks = TOTAL,
		.f_bfree = TOTAL - USED,
		.f_bavail = AVAIL,
		.f_bresvd = TOTAL - USED - AVAIL,
		.f_mntfromname = "/dev/wd0e",
		.f_mntonname = "/mount/windows/C",
#undef AVAIL
#undef USED
#undef TOTAL
#undef BSIZE
	};

	*getnewstatvfs() = tmpl;
}