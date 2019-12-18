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
struct voistat {int /*<<< orphan*/  errs; int /*<<< orphan*/  data_off; int /*<<< orphan*/  dsz; int /*<<< orphan*/  dtype; int /*<<< orphan*/  stype; } ;
struct voi {int /*<<< orphan*/  dtype; int /*<<< orphan*/  id; } ;
struct statsblobv1 {int /*<<< orphan*/  tplhash; } ;
struct sb_visitcb_ctx {int (* cb ) (struct sb_visit*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  usrctx; } ;
struct sb_visit {int flags; int /*<<< orphan*/  vs_errs; int /*<<< orphan*/  vs_data; int /*<<< orphan*/  vs_dsz; int /*<<< orphan*/  vs_dtype; int /*<<< orphan*/  vs_stype; int /*<<< orphan*/  voi_dtype; int /*<<< orphan*/  voi_id; int /*<<< orphan*/  tplhash; } ;
struct sb_iter_ctx {int flags; struct sb_visitcb_ctx* usrctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOB_OFFSET (struct statsblobv1*,int /*<<< orphan*/ ) ; 
 int SB_IT_FIRST_CB ; 
 int SB_IT_FIRST_VOI ; 
 int SB_IT_FIRST_VOISTAT ; 
 int SB_IT_LAST_CB ; 
 int SB_IT_LAST_VOI ; 
 int SB_IT_LAST_VOISTAT ; 
 int stub1 (struct sb_visit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stats_v1_itercb_visit(struct statsblobv1 *sb, struct voi *v,
    struct voistat *vs, struct sb_iter_ctx *ctx)
{
	struct sb_visitcb_ctx *vctx;
	struct sb_visit sbv;

	vctx = ctx->usrctx;

	sbv.tplhash = sb->tplhash;
	sbv.voi_id = v->id;
	sbv.voi_dtype = v->dtype;
	sbv.vs_stype = vs->stype;
	sbv.vs_dtype = vs->dtype;
	sbv.vs_dsz = vs->dsz;
	sbv.vs_data = BLOB_OFFSET(sb, vs->data_off);
	sbv.vs_errs = vs->errs;
	sbv.flags = ctx->flags & (SB_IT_FIRST_CB | SB_IT_LAST_CB |
	    SB_IT_FIRST_VOI | SB_IT_LAST_VOI | SB_IT_FIRST_VOISTAT |
	    SB_IT_LAST_VOISTAT);

	return (vctx->cb(&sbv, vctx->usrctx));
}