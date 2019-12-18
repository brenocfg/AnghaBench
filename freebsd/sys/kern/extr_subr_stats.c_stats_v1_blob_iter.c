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
typedef  int uint32_t ;
struct voistat {scalar_t__ stype; } ;
struct voi {scalar_t__ id; int voistatmaxid; int /*<<< orphan*/  stats_off; } ;
struct statsblobv1 {struct voi* vois; } ;
struct sb_iter_ctx {int flags; int vslot; int vsslot; void* usrctx; } ;
typedef  scalar_t__ (* stats_v1_blob_itercb_t ) (struct statsblobv1*,struct voi*,struct voistat*,struct sb_iter_ctx*) ;

/* Variables and functions */
 scalar_t__ BLOB_OFFSET (struct statsblobv1*,int /*<<< orphan*/ ) ; 
 int NVOIS (struct statsblobv1*) ; 
 int SB_IT_FIRST_CB ; 
 int SB_IT_FIRST_VOI ; 
 int SB_IT_FIRST_VOISTAT ; 
 int SB_IT_LAST_CB ; 
 int SB_IT_LAST_VOI ; 
 int SB_IT_LAST_VOISTAT ; 
 int SB_IT_NULLVOI ; 
 int SB_IT_NULLVOISTAT ; 

__attribute__((used)) static void
stats_v1_blob_iter(struct statsblobv1 *sb, stats_v1_blob_itercb_t icb,
    void *usrctx, uint32_t flags)
{
	struct voi *v;
	struct voistat *vs;
	struct sb_iter_ctx ctx;
	int i, j, firstvoi;

	ctx.usrctx = usrctx;
	ctx.flags |= SB_IT_FIRST_CB;
	ctx.flags &= ~(SB_IT_FIRST_VOI | SB_IT_LAST_VOI | SB_IT_FIRST_VOISTAT |
	    SB_IT_LAST_VOISTAT);
	firstvoi = 1;

	for (i = 0; i < NVOIS(sb); i++) {
		v = &sb->vois[i];
		ctx.vslot = i;
		ctx.vsslot = -1;
		ctx.flags |= SB_IT_FIRST_VOISTAT;

		if (firstvoi)
			ctx.flags |= SB_IT_FIRST_VOI;
		else if (i == (NVOIS(sb) - 1))
			ctx.flags |= SB_IT_LAST_VOI | SB_IT_LAST_CB;

		if (v->id < 0 && (flags & SB_IT_NULLVOI)) {
			if (icb(sb, v, NULL, &ctx))
				return;
			firstvoi = 0;
			ctx.flags &= ~SB_IT_FIRST_CB;
		}

		/* If NULL voi, v->voistatmaxid == -1 */
		for (j = 0; j <= v->voistatmaxid; j++) {
			vs = &((struct voistat *)BLOB_OFFSET(sb,
			    v->stats_off))[j];
			if (vs->stype < 0 &&
			    !(flags & SB_IT_NULLVOISTAT))
				continue;

			if (j == v->voistatmaxid) {
				ctx.flags |= SB_IT_LAST_VOISTAT;
				if (i == (NVOIS(sb) - 1))
					ctx.flags |=
					    SB_IT_LAST_CB;
			} else
				ctx.flags &= ~SB_IT_LAST_CB;

			ctx.vsslot = j;
			if (icb(sb, v, vs, &ctx))
				return;

			ctx.flags &= ~(SB_IT_FIRST_CB | SB_IT_FIRST_VOISTAT |
			    SB_IT_LAST_VOISTAT);
		}
		ctx.flags &= ~(SB_IT_FIRST_VOI | SB_IT_LAST_VOI);
	}
}