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
struct voistat {int dummy; } ;
struct voi {int dummy; } ;
struct statsblobv1 {int dummy; } ;
struct sb_tostrcb_ctx {int fmt; int /*<<< orphan*/  buf; } ;
struct sb_iter_ctx {struct sb_tostrcb_ctx* usrctx; } ;

/* Variables and functions */
#define  SB_STRFMT_FREEFORM 129 
#define  SB_STRFMT_JSON 128 
 int sbuf_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_v1_itercb_tostr_freeform (struct statsblobv1*,struct voi*,struct voistat*,struct sb_iter_ctx*) ; 
 int /*<<< orphan*/  stats_v1_itercb_tostr_json (struct statsblobv1*,struct voi*,struct voistat*,struct sb_iter_ctx*) ; 

__attribute__((used)) static int
stats_v1_itercb_tostr(struct statsblobv1 *sb, struct voi *v, struct voistat *vs,
    struct sb_iter_ctx *ctx)
{
	struct sb_tostrcb_ctx *sctx;

	sctx = ctx->usrctx;

	switch (sctx->fmt) {
	case SB_STRFMT_FREEFORM:
		stats_v1_itercb_tostr_freeform(sb, v, vs, ctx);
		break;
	case SB_STRFMT_JSON:
		stats_v1_itercb_tostr_json(sb, v, vs, ctx);
		break;
	default:
		break;
	}

	return (sbuf_error(sctx->buf));
}