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
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct statfs {int f_bsize; int f_files; int f_ffree; void* f_bavail; void* f_bfree; void* f_blocks; } ;
struct mdchain {int dummy; } ;
struct mbchain {int dummy; } ;
struct smb_t2rq {int t2_maxpcount; int t2_maxdcount; struct mdchain t2_rdata; struct mbchain t2_tparam; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_QUERY_FS_SIZE_INFO ; 
 int /*<<< orphan*/  SMB_TRANS2_QUERY_FS_INFORMATION ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 int /*<<< orphan*/  mb_init (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_get_int64le (struct mdchain*,scalar_t__*) ; 
 int /*<<< orphan*/  md_get_uint32le (struct mdchain*,int*) ; 
 int smb_t2_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_t2rq**) ; 
 int /*<<< orphan*/  smb_t2_done (struct smb_t2rq*) ; 
 int smb_t2_request (struct smb_t2rq*) ; 

__attribute__((used)) static int
smbfs_query_info_fs(struct smb_share *ssp, struct statfs *sbp,
	struct smb_cred *scred)
{
	struct smb_t2rq *t2p;
	struct mbchain *mbp;
	struct mdchain *mdp;
	uint32_t bsize, bpu;
	int64_t units, funits;
	int error;

	error = smb_t2_alloc(SSTOCP(ssp), SMB_TRANS2_QUERY_FS_INFORMATION,
	    scred, &t2p);
	if (error)
		return (error);
	mbp = &t2p->t2_tparam;
	mb_init(mbp);
	mb_put_uint16le(mbp, SMB_QUERY_FS_SIZE_INFO);
	t2p->t2_maxpcount = 2;
	t2p->t2_maxdcount = sizeof(int64_t) * 2 + sizeof(uint32_t) * 2;
	error = smb_t2_request(t2p);
	if (error) {
		smb_t2_done(t2p);
		return (error);
	}
	mdp = &t2p->t2_rdata;
	md_get_int64le(mdp, &units);
	md_get_int64le(mdp, &funits);
	md_get_uint32le(mdp, &bpu);
	md_get_uint32le(mdp, &bsize);
	sbp->f_bsize = bpu * bsize;	/* fundamental filesystem block size */
	sbp->f_blocks= (uint64_t)units;	/* total data blocks in filesystem */
	sbp->f_bfree = (uint64_t)funits;/* free blocks in fs */
	sbp->f_bavail= (uint64_t)funits;/* free blocks avail to non-superuser */
	sbp->f_files = 0xffff;		/* total file nodes in filesystem */
	sbp->f_ffree = 0xffff;		/* free file nodes in fs */
	smb_t2_done(t2p);
	return (0);
}