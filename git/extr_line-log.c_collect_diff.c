#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct collect_diff_cbdata* priv; int /*<<< orphan*/  hunk_func; scalar_t__ interhunkctxlen; scalar_t__ ctxlen; } ;
typedef  TYPE_1__ xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  TYPE_1__ xdemitconf_t ;
typedef  TYPE_1__ xdemitcb_t ;
struct diff_ranges {int dummy; } ;
struct collect_diff_cbdata {struct diff_ranges* diff; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  ecb ;

/* Variables and functions */
 int /*<<< orphan*/  collect_diff_cb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int xdi_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int collect_diff(mmfile_t *parent, mmfile_t *target, struct diff_ranges *out)
{
	struct collect_diff_cbdata cbdata = {NULL};
	xpparam_t xpp;
	xdemitconf_t xecfg;
	xdemitcb_t ecb;

	memset(&xpp, 0, sizeof(xpp));
	memset(&xecfg, 0, sizeof(xecfg));
	xecfg.ctxlen = xecfg.interhunkctxlen = 0;

	cbdata.diff = out;
	xecfg.hunk_func = collect_diff_cb;
	memset(&ecb, 0, sizeof(ecb));
	ecb.priv = &cbdata;
	return xdi_diff(parent, target, &xpp, &xecfg, &ecb);
}