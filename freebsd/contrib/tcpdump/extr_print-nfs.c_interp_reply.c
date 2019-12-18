#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sunrpc_msg {int dummy; } ;
struct TYPE_19__ {int ndo_vflag; int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (scalar_t__ const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (scalar_t__ const) ; 
#define  NFSPROC_ACCESS 148 
#define  NFSPROC_COMMIT 147 
#define  NFSPROC_CREATE 146 
#define  NFSPROC_FSINFO 145 
#define  NFSPROC_FSSTAT 144 
#define  NFSPROC_GETATTR 143 
#define  NFSPROC_LINK 142 
#define  NFSPROC_LOOKUP 141 
#define  NFSPROC_MKDIR 140 
#define  NFSPROC_MKNOD 139 
#define  NFSPROC_PATHCONF 138 
#define  NFSPROC_READ 137 
#define  NFSPROC_READDIR 136 
#define  NFSPROC_READDIRPLUS 135 
#define  NFSPROC_READLINK 134 
#define  NFSPROC_REMOVE 133 
#define  NFSPROC_RENAME 132 
#define  NFSPROC_RMDIR 131 
#define  NFSPROC_SETATTR 130 
#define  NFSPROC_SYMLINK 129 
#define  NFSPROC_WRITE 128 
 scalar_t__ NFS_NPROCS ; 
 scalar_t__ NFS_VER3 ; 
 int /*<<< orphan*/  nfserr ; 
 int /*<<< orphan*/  nfsproc_str ; 
 scalar_t__* nfsv3_procid ; 
 int /*<<< orphan*/  nfsv3_writemodes ; 
 scalar_t__* parse_post_op_attr (TYPE_1__*,scalar_t__ const*,int) ; 
 scalar_t__* parse_wcc_data (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  parseattrstat (TYPE_1__*,scalar_t__ const*,int,int) ; 
 int /*<<< orphan*/ * parsecreateopres (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  parsediropres (TYPE_1__*,scalar_t__ const*) ; 
 scalar_t__* parsefh (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  parsefsinfo (TYPE_1__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  parselinkres (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  parsepathconf (TYPE_1__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  parserddires (TYPE_1__*,scalar_t__ const*) ; 
 scalar_t__* parserep (TYPE_1__*,struct sunrpc_msg const*,int) ; 
 int /*<<< orphan*/  parsestatfs (TYPE_1__*,scalar_t__ const*,int) ; 
 scalar_t__* parsestatus (TYPE_1__*,scalar_t__ const*,int*) ; 
 int /*<<< orphan*/  parsev3rddirres (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  parsewccres (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
interp_reply(netdissect_options *ndo,
             const struct sunrpc_msg *rp, uint32_t proc, uint32_t vers, int length)
{
	register const uint32_t *dp;
	register int v3;
	int er;

	v3 = (vers == NFS_VER3);

	if (!v3 && proc < NFS_NPROCS)
		proc = nfsv3_procid[proc];

	ND_PRINT((ndo, " %s", tok2str(nfsproc_str, "proc-%u", proc)));
	switch (proc) {

	case NFSPROC_GETATTR:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parseattrstat(ndo, dp, !ndo->ndo_qflag, v3) != 0)
			return;
		break;

	case NFSPROC_SETATTR:
		if (!(dp = parserep(ndo, rp, length)))
			return;
		if (v3) {
			if (parsewccres(ndo, dp, ndo->ndo_vflag))
				return;
		} else {
			if (parseattrstat(ndo, dp, !ndo->ndo_qflag, 0) != 0)
				return;
		}
		break;

	case NFSPROC_LOOKUP:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(ndo, dp, &er)))
				break;
			if (er) {
				if (ndo->ndo_vflag > 1) {
					ND_PRINT((ndo, " post dattr:"));
					dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag);
				}
			} else {
				if (!(dp = parsefh(ndo, dp, v3)))
					break;
				if ((dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)) &&
				    ndo->ndo_vflag > 1) {
					ND_PRINT((ndo, " post dattr:"));
					dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag);
				}
			}
			if (dp)
				return;
		} else {
			if (parsediropres(ndo, dp) != 0)
				return;
		}
		break;

	case NFSPROC_ACCESS:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (!(dp = parsestatus(ndo, dp, &er)))
			break;
		if (ndo->ndo_vflag)
			ND_PRINT((ndo, " attr:"));
		if (!(dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)))
			break;
		if (!er) {
			ND_TCHECK(dp[0]);
			ND_PRINT((ndo, " c %04x", EXTRACT_32BITS(&dp[0])));
		}
		return;

	case NFSPROC_READLINK:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parselinkres(ndo, dp, v3) != 0)
			return;
		break;

	case NFSPROC_READ:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(ndo, dp, &er)))
				break;
			if (!(dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)))
				break;
			if (er)
				return;
			if (ndo->ndo_vflag) {
				ND_TCHECK(dp[1]);
				ND_PRINT((ndo, " %u bytes", EXTRACT_32BITS(&dp[0])));
				if (EXTRACT_32BITS(&dp[1]))
					ND_PRINT((ndo, " EOF"));
			}
			return;
		} else {
			if (parseattrstat(ndo, dp, ndo->ndo_vflag, 0) != 0)
				return;
		}
		break;

	case NFSPROC_WRITE:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(ndo, dp, &er)))
				break;
			if (!(dp = parse_wcc_data(ndo, dp, ndo->ndo_vflag)))
				break;
			if (er)
				return;
			if (ndo->ndo_vflag) {
				ND_TCHECK(dp[0]);
				ND_PRINT((ndo, " %u bytes", EXTRACT_32BITS(&dp[0])));
				if (ndo->ndo_vflag > 1) {
					ND_TCHECK(dp[1]);
					ND_PRINT((ndo, " <%s>",
						tok2str(nfsv3_writemodes,
							NULL, EXTRACT_32BITS(&dp[1]))));
				}
				return;
			}
		} else {
			if (parseattrstat(ndo, dp, ndo->ndo_vflag, v3) != 0)
				return;
		}
		break;

	case NFSPROC_CREATE:
	case NFSPROC_MKDIR:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (parsecreateopres(ndo, dp, ndo->ndo_vflag) != NULL)
				return;
		} else {
			if (parsediropres(ndo, dp) != 0)
				return;
		}
		break;

	case NFSPROC_SYMLINK:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (parsecreateopres(ndo, dp, ndo->ndo_vflag) != NULL)
				return;
		} else {
			if (parsestatus(ndo, dp, &er) != NULL)
				return;
		}
		break;

	case NFSPROC_MKNOD:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (parsecreateopres(ndo, dp, ndo->ndo_vflag) != NULL)
			return;
		break;

	case NFSPROC_REMOVE:
	case NFSPROC_RMDIR:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (parsewccres(ndo, dp, ndo->ndo_vflag))
				return;
		} else {
			if (parsestatus(ndo, dp, &er) != NULL)
				return;
		}
		break;

	case NFSPROC_RENAME:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(ndo, dp, &er)))
				break;
			if (ndo->ndo_vflag) {
				ND_PRINT((ndo, " from:"));
				if (!(dp = parse_wcc_data(ndo, dp, ndo->ndo_vflag)))
					break;
				ND_PRINT((ndo, " to:"));
				if (!(dp = parse_wcc_data(ndo, dp, ndo->ndo_vflag)))
					break;
			}
			return;
		} else {
			if (parsestatus(ndo, dp, &er) != NULL)
				return;
		}
		break;

	case NFSPROC_LINK:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(ndo, dp, &er)))
				break;
			if (ndo->ndo_vflag) {
				ND_PRINT((ndo, " file POST:"));
				if (!(dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)))
					break;
				ND_PRINT((ndo, " dir:"));
				if (!(dp = parse_wcc_data(ndo, dp, ndo->ndo_vflag)))
					break;
				return;
			}
		} else {
			if (parsestatus(ndo, dp, &er) != NULL)
				return;
		}
		break;

	case NFSPROC_READDIR:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (v3) {
			if (parsev3rddirres(ndo, dp, ndo->ndo_vflag))
				return;
		} else {
			if (parserddires(ndo, dp) != 0)
				return;
		}
		break;

	case NFSPROC_READDIRPLUS:
		if (!(dp = parserep(ndo, rp, length)))
			break;
		if (parsev3rddirres(ndo, dp, ndo->ndo_vflag))
			return;
		break;

	case NFSPROC_FSSTAT:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parsestatfs(ndo, dp, v3) != 0)
			return;
		break;

	case NFSPROC_FSINFO:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parsefsinfo(ndo, dp) != 0)
			return;
		break;

	case NFSPROC_PATHCONF:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parsepathconf(ndo, dp) != 0)
			return;
		break;

	case NFSPROC_COMMIT:
		dp = parserep(ndo, rp, length);
		if (dp != NULL && parsewccres(ndo, dp, ndo->ndo_vflag) != 0)
			return;
		break;

	default:
		return;
	}
trunc:
	if (!nfserr)
		ND_PRINT((ndo, "%s", tstr));
}