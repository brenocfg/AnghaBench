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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {void* nfsv3_nsec; void* nfsv3_sec; } ;
struct TYPE_3__ {void* nfsv3_nsec; void* nfsv3_sec; } ;
struct nfsv3_sattr {scalar_t__ sa_atimetype; scalar_t__ sa_mtimetype; TYPE_2__ sa_mtime; TYPE_1__ sa_atime; void* sa_size; void* sa_sizeset; void* sa_gid; void* sa_gidset; void* sa_uid; void* sa_uidset; void* sa_mode; void* sa_modeset; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 void* EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 scalar_t__ NFSV3SATTRTIME_TOCLIENT ; 

__attribute__((used)) static const uint32_t *
parse_sattr3(netdissect_options *ndo,
             const uint32_t *dp, struct nfsv3_sattr *sa3)
{
	ND_TCHECK(dp[0]);
	sa3->sa_modeset = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_modeset) {
		ND_TCHECK(dp[0]);
		sa3->sa_mode = EXTRACT_32BITS(dp);
		dp++;
	}

	ND_TCHECK(dp[0]);
	sa3->sa_uidset = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_uidset) {
		ND_TCHECK(dp[0]);
		sa3->sa_uid = EXTRACT_32BITS(dp);
		dp++;
	}

	ND_TCHECK(dp[0]);
	sa3->sa_gidset = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_gidset) {
		ND_TCHECK(dp[0]);
		sa3->sa_gid = EXTRACT_32BITS(dp);
		dp++;
	}

	ND_TCHECK(dp[0]);
	sa3->sa_sizeset = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_sizeset) {
		ND_TCHECK(dp[0]);
		sa3->sa_size = EXTRACT_32BITS(dp);
		dp++;
	}

	ND_TCHECK(dp[0]);
	sa3->sa_atimetype = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_atimetype == NFSV3SATTRTIME_TOCLIENT) {
		ND_TCHECK(dp[1]);
		sa3->sa_atime.nfsv3_sec = EXTRACT_32BITS(dp);
		dp++;
		sa3->sa_atime.nfsv3_nsec = EXTRACT_32BITS(dp);
		dp++;
	}

	ND_TCHECK(dp[0]);
	sa3->sa_mtimetype = EXTRACT_32BITS(dp);
	dp++;
	if (sa3->sa_mtimetype == NFSV3SATTRTIME_TOCLIENT) {
		ND_TCHECK(dp[1]);
		sa3->sa_mtime.nfsv3_sec = EXTRACT_32BITS(dp);
		dp++;
		sa3->sa_mtime.nfsv3_nsec = EXTRACT_32BITS(dp);
		dp++;
	}

	return dp;
trunc:
	return NULL;
}