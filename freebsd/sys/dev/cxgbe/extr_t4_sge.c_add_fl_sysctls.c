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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sge_fl {int sidx; int flags; int /*<<< orphan*/  cl_fast_recycled; int /*<<< orphan*/  cl_recycled; int /*<<< orphan*/  cl_allocated; int /*<<< orphan*/  mbuf_inlined; int /*<<< orphan*/  mbuf_allocated; int /*<<< orphan*/  pidx; int /*<<< orphan*/  rx_offset; int /*<<< orphan*/  cidx; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  ba; } ;
struct TYPE_3__ {scalar_t__ spg_len; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int EQ_ESIZE ; 
 int FL_BUF_PACKING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UAUTO (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ fl_pad ; 
 int /*<<< orphan*/  sysctl_uint16 ; 

__attribute__((used)) static void
add_fl_sysctls(struct adapter *sc, struct sysctl_ctx_list *ctx,
    struct sysctl_oid *oid, struct sge_fl *fl)
{
	struct sysctl_oid_list *children = SYSCTL_CHILDREN(oid);

	oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, "fl", CTLFLAG_RD, NULL,
	    "freelist");
	children = SYSCTL_CHILDREN(oid);

	SYSCTL_ADD_UAUTO(ctx, children, OID_AUTO, "ba", CTLFLAG_RD,
	    &fl->ba, "bus address of descriptor ring");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "dmalen", CTLFLAG_RD, NULL,
	    fl->sidx * EQ_ESIZE + sc->params.sge.spg_len,
	    "desc ring size in bytes");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "cntxt_id",
	    CTLTYPE_INT | CTLFLAG_RD, &fl->cntxt_id, 0, sysctl_uint16, "I",
	    "SGE context id of the freelist");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "padding", CTLFLAG_RD, NULL,
	    fl_pad ? 1 : 0, "padding enabled");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "packing", CTLFLAG_RD, NULL,
	    fl->flags & FL_BUF_PACKING ? 1 : 0, "packing enabled");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "cidx", CTLFLAG_RD, &fl->cidx,
	    0, "consumer index");
	if (fl->flags & FL_BUF_PACKING) {
		SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "rx_offset",
		    CTLFLAG_RD, &fl->rx_offset, 0, "packing rx offset");
	}
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "pidx", CTLFLAG_RD, &fl->pidx,
	    0, "producer index");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "mbuf_allocated",
	    CTLFLAG_RD, &fl->mbuf_allocated, "# of mbuf allocated");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "mbuf_inlined",
	    CTLFLAG_RD, &fl->mbuf_inlined, "# of mbuf inlined in clusters");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "cluster_allocated",
	    CTLFLAG_RD, &fl->cl_allocated, "# of clusters allocated");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "cluster_recycled",
	    CTLFLAG_RD, &fl->cl_recycled, "# of clusters recycled");
	SYSCTL_ADD_UQUAD(ctx, children, OID_AUTO, "cluster_fast_recycled",
	    CTLFLAG_RD, &fl->cl_fast_recycled, "# of clusters recycled (fast)");
}