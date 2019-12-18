#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sge_params {int /*<<< orphan*/  pack_boundary; int /*<<< orphan*/  spg_len; int /*<<< orphan*/  pad_boundary; int /*<<< orphan*/  fl_pktshift; } ;
struct TYPE_2__ {struct sge_params sge; } ;
struct adapter {int /*<<< orphan*/  sge; TYPE_1__ params; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cong_drop ; 
 int /*<<< orphan*/  sysctl_bufsizes ; 

void
t4_sge_sysctls(struct adapter *sc, struct sysctl_ctx_list *ctx,
    struct sysctl_oid_list *children)
{
	struct sge_params *sp = &sc->params.sge;

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "buffer_sizes",
	    CTLTYPE_STRING | CTLFLAG_RD, &sc->sge, 0, sysctl_bufsizes, "A",
	    "freelist buffer sizes");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "fl_pktshift", CTLFLAG_RD,
	    NULL, sp->fl_pktshift, "payload DMA offset in rx buffer (bytes)");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "fl_pad", CTLFLAG_RD,
	    NULL, sp->pad_boundary, "payload pad boundary (bytes)");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "spg_len", CTLFLAG_RD,
	    NULL, sp->spg_len, "status page size (bytes)");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "cong_drop", CTLFLAG_RD,
	    NULL, cong_drop, "congestion drop setting");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "fl_pack", CTLFLAG_RD,
	    NULL, sp->pack_boundary, "payload pack boundary (bytes)");
}