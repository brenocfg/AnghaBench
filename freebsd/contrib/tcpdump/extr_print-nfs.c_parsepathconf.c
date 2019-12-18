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
typedef  int /*<<< orphan*/  uint32_t ;
struct nfsv3_pathconf {int /*<<< orphan*/  pc_casepreserving; int /*<<< orphan*/  pc_caseinsensitive; int /*<<< orphan*/  pc_chownrestricted; int /*<<< orphan*/  pc_notrunc; int /*<<< orphan*/  pc_namemax; int /*<<< orphan*/  pc_linkmax; } ;
struct TYPE_6__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct nfsv3_pathconf const) ; 
 int /*<<< orphan*/ * parse_post_op_attr (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/ * parsestatus (TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int
parsepathconf(netdissect_options *ndo,
              const uint32_t *dp)
{
	int er;
	const struct nfsv3_pathconf *spp;

	if (!(dp = parsestatus(ndo, dp, &er)))
		return (0);
	if (ndo->ndo_vflag)
		ND_PRINT((ndo, " POST:"));
	if (!(dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)))
		return (0);
	if (er)
		return (1);

	spp = (const struct nfsv3_pathconf *)dp;
	ND_TCHECK(*spp);

	ND_PRINT((ndo, " linkmax %u namemax %u %s %s %s %s",
	       EXTRACT_32BITS(&spp->pc_linkmax),
	       EXTRACT_32BITS(&spp->pc_namemax),
	       EXTRACT_32BITS(&spp->pc_notrunc) ? "notrunc" : "",
	       EXTRACT_32BITS(&spp->pc_chownrestricted) ? "chownres" : "",
	       EXTRACT_32BITS(&spp->pc_caseinsensitive) ? "igncase" : "",
	       EXTRACT_32BITS(&spp->pc_casepreserving) ? "keepcase" : ""));
	return (1);
trunc:
	return (0);
}