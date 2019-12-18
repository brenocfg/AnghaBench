#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sunrpc_msg {int /*<<< orphan*/  rm_xid; } ;
typedef  int /*<<< orphan*/  srcid ;
struct TYPE_6__ {int /*<<< orphan*/  ndo_nflag; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  dstid ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int NFS_PORT ; 
 scalar_t__ nfserr ; 
 int /*<<< orphan*/  nfsreply_print_noaddr (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  print_nfsaddr (TYPE_1__*,int /*<<< orphan*/  const*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
nfsreply_print(netdissect_options *ndo,
               register const u_char *bp, u_int length,
               register const u_char *bp2)
{
	register const struct sunrpc_msg *rp;
	char srcid[20], dstid[20];	/*fits 32bit*/

	nfserr = 0;		/* assume no error */
	rp = (const struct sunrpc_msg *)bp;

	ND_TCHECK(rp->rm_xid);
	if (!ndo->ndo_nflag) {
		strlcpy(srcid, "nfs", sizeof(srcid));
		snprintf(dstid, sizeof(dstid), "%u",
		    EXTRACT_32BITS(&rp->rm_xid));
	} else {
		snprintf(srcid, sizeof(srcid), "%u", NFS_PORT);
		snprintf(dstid, sizeof(dstid), "%u",
		    EXTRACT_32BITS(&rp->rm_xid));
	}
	print_nfsaddr(ndo, bp2, srcid, dstid);

	nfsreply_print_noaddr(ndo, bp, length, bp2);
	return;

trunc:
	if (!nfserr)
		ND_PRINT((ndo, "%s", tstr));
}