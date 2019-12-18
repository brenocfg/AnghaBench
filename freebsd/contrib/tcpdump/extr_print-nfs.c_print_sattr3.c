#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nfsv3_nsec; int /*<<< orphan*/  nfsv3_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfsv3_nsec; int /*<<< orphan*/  nfsv3_sec; } ;
struct nfsv3_sattr {scalar_t__ sa_atimetype; scalar_t__ sa_mtimetype; TYPE_2__ sa_mtime; TYPE_1__ sa_atime; int /*<<< orphan*/  sa_gid; scalar_t__ sa_gidset; int /*<<< orphan*/  sa_uid; scalar_t__ sa_uidset; int /*<<< orphan*/  sa_mode; scalar_t__ sa_modeset; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ NFSV3SATTRTIME_TOCLIENT ; 

__attribute__((used)) static void
print_sattr3(netdissect_options *ndo,
             const struct nfsv3_sattr *sa3, int verbose)
{
	if (sa3->sa_modeset)
		ND_PRINT((ndo, " mode %o", sa3->sa_mode));
	if (sa3->sa_uidset)
		ND_PRINT((ndo, " uid %u", sa3->sa_uid));
	if (sa3->sa_gidset)
		ND_PRINT((ndo, " gid %u", sa3->sa_gid));
	if (verbose > 1) {
		if (sa3->sa_atimetype == NFSV3SATTRTIME_TOCLIENT)
			ND_PRINT((ndo, " atime %u.%06u", sa3->sa_atime.nfsv3_sec,
			       sa3->sa_atime.nfsv3_nsec));
		if (sa3->sa_mtimetype == NFSV3SATTRTIME_TOCLIENT)
			ND_PRINT((ndo, " mtime %u.%06u", sa3->sa_mtime.nfsv3_sec,
			       sa3->sa_mtime.nfsv3_nsec));
	}
}