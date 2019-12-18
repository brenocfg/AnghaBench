#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fhe_stats_sysctl; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_reqs_per_nfsd; int /*<<< orphan*/  max_nfsds_per_fh; int /*<<< orphan*/  bin_shift; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  enable; } ;
struct fha_params {TYPE_3__ callbacks; int /*<<< orphan*/  sysctl_tree; int /*<<< orphan*/  sysctl_ctx; TYPE_2__ ctls; TYPE_1__* fha_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  FHA_DEF_BIN_SHIFT ; 
 int /*<<< orphan*/  FHA_DEF_ENABLE ; 
 int /*<<< orphan*/  FHA_DEF_MAX_NFSDS_PER_FH ; 
 int /*<<< orphan*/  FHA_DEF_MAX_REQS_PER_NFSD ; 
 int /*<<< orphan*/  FHA_DEF_READ ; 
 int /*<<< orphan*/  FHA_DEF_WRITE ; 
 int FHA_HASH_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_OID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fha_init(struct fha_params *softc)
{
	int i;

	for (i = 0; i < FHA_HASH_SIZE; i++)
		mtx_init(&softc->fha_hash[i].mtx, "fhalock", NULL, MTX_DEF);

	/*
	 * Set the default tuning parameters.
	 */
	softc->ctls.enable = FHA_DEF_ENABLE;
	softc->ctls.read = FHA_DEF_READ;
	softc->ctls.write = FHA_DEF_WRITE;
	softc->ctls.bin_shift = FHA_DEF_BIN_SHIFT;
	softc->ctls.max_nfsds_per_fh = FHA_DEF_MAX_NFSDS_PER_FH;
	softc->ctls.max_reqs_per_nfsd = FHA_DEF_MAX_REQS_PER_NFSD;

	/*
	 * Add sysctls so the user can change the tuning parameters.
	 */
	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "enable", CTLFLAG_RWTUN,
	    &softc->ctls.enable, 0, "Enable NFS File Handle Affinity (FHA)");

	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "read", CTLFLAG_RWTUN,
	    &softc->ctls.read, 0, "Enable NFS FHA read locality");

	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "write", CTLFLAG_RWTUN,
	    &softc->ctls.write, 0, "Enable NFS FHA write locality");

	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "bin_shift", CTLFLAG_RWTUN,
	    &softc->ctls.bin_shift, 0, "Maximum locality distance 2^(bin_shift) bytes");

	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "max_nfsds_per_fh", CTLFLAG_RWTUN,
	    &softc->ctls.max_nfsds_per_fh, 0, "Maximum nfsd threads that "
	    "should be working on requests for the same file handle");

	SYSCTL_ADD_UINT(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "max_reqs_per_nfsd", CTLFLAG_RWTUN,
	    &softc->ctls.max_reqs_per_nfsd, 0, "Maximum requests that "
	    "single nfsd thread should be working on at any time");

	SYSCTL_ADD_OID(&softc->sysctl_ctx, SYSCTL_CHILDREN(softc->sysctl_tree),
	    OID_AUTO, "fhe_stats", CTLTYPE_STRING | CTLFLAG_RD, 0, 0,
	    softc->callbacks.fhe_stats_sysctl, "A", "");

}