#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpparam_t ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  ctxlen; } ;
typedef  TYPE_1__ xdemitconf_t ;
typedef  int /*<<< orphan*/  xdemitcb_t ;
struct TYPE_12__ {scalar_t__ size; } ;
typedef  TYPE_2__ mmfile_t ;

/* Variables and functions */
 scalar_t__ MAX_XDIFF_SIZE ; 
 int XDL_EMIT_FUNCCONTEXT ; 
 int /*<<< orphan*/  trim_common_tail (TYPE_2__*,TYPE_2__*) ; 
 int xdl_diff (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

int xdi_diff(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp, xdemitconf_t const *xecfg, xdemitcb_t *xecb)
{
	mmfile_t a = *mf1;
	mmfile_t b = *mf2;

	if (mf1->size > MAX_XDIFF_SIZE || mf2->size > MAX_XDIFF_SIZE)
		return -1;

	if (!xecfg->ctxlen && !(xecfg->flags & XDL_EMIT_FUNCCONTEXT))
		trim_common_tail(&a, &b);

	return xdl_diff(&a, &b, xpp, xecfg, xecb);
}