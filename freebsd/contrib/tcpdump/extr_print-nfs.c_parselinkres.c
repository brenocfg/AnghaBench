#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/ * parse_post_op_attr (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parsefn (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * parsestatus (TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int
parselinkres(netdissect_options *ndo,
             const uint32_t *dp, int v3)
{
	int er;

	dp = parsestatus(ndo, dp, &er);
	if (dp == NULL)
		return(0);
	if (er)
		return(1);
	if (v3 && !(dp = parse_post_op_attr(ndo, dp, ndo->ndo_vflag)))
		return (0);
	ND_PRINT((ndo, " "));
	return (parsefn(ndo, dp) != NULL);
}