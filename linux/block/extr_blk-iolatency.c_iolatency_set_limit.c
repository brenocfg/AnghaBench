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
typedef  scalar_t__ u64 ;
struct kernfs_open_file {int dummy; } ;
struct iolatency_grp {scalar_t__ min_lat_nsec; struct blk_iolatency* blkiolat; } ;
struct blkg_conf_ctx {char* body; struct blkcg_gq* blkg; } ;
struct blkcg_gq {int /*<<< orphan*/  q; } ;
struct blkcg {int dummy; } ;
struct blk_iolatency {int /*<<< orphan*/  enabled; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSEC_PER_USEC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcg_policy_iolatency ; 
 int /*<<< orphan*/  blkg_conf_finish (struct blkg_conf_ctx*) ; 
 int blkg_conf_prep (struct blkcg*,int /*<<< orphan*/ *,char*,struct blkg_conf_ctx*) ; 
 int /*<<< orphan*/  blkg_get (struct blkcg_gq*) ; 
 int /*<<< orphan*/  blkg_put (struct blkcg_gq*) ; 
 struct iolatency_grp* blkg_to_lat (struct blkcg_gq*) ; 
 struct blkcg* css_to_blkcg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iolatency_clear_scaling (struct blkcg_gq*) ; 
 int iolatency_set_min_lat_nsec (struct blkcg_gq*,scalar_t__) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int sscanf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t iolatency_set_limit(struct kernfs_open_file *of, char *buf,
			     size_t nbytes, loff_t off)
{
	struct blkcg *blkcg = css_to_blkcg(of_css(of));
	struct blkcg_gq *blkg;
	struct blkg_conf_ctx ctx;
	struct iolatency_grp *iolat;
	char *p, *tok;
	u64 lat_val = 0;
	u64 oldval;
	int ret;
	int enable = 0;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_iolatency, buf, &ctx);
	if (ret)
		return ret;

	iolat = blkg_to_lat(ctx.blkg);
	p = ctx.body;

	ret = -EINVAL;
	while ((tok = strsep(&p, " "))) {
		char key[16];
		char val[21];	/* 18446744073709551616 */

		if (sscanf(tok, "%15[^=]=%20s", key, val) != 2)
			goto out;

		if (!strcmp(key, "target")) {
			u64 v;

			if (!strcmp(val, "max"))
				lat_val = 0;
			else if (sscanf(val, "%llu", &v) == 1)
				lat_val = v * NSEC_PER_USEC;
			else
				goto out;
		} else {
			goto out;
		}
	}

	/* Walk up the tree to see if our new val is lower than it should be. */
	blkg = ctx.blkg;
	oldval = iolat->min_lat_nsec;

	enable = iolatency_set_min_lat_nsec(blkg, lat_val);
	if (enable) {
		WARN_ON_ONCE(!blk_get_queue(blkg->q));
		blkg_get(blkg);
	}

	if (oldval != iolat->min_lat_nsec) {
		iolatency_clear_scaling(blkg);
	}

	ret = 0;
out:
	blkg_conf_finish(&ctx);
	if (ret == 0 && enable) {
		struct iolatency_grp *tmp = blkg_to_lat(blkg);
		struct blk_iolatency *blkiolat = tmp->blkiolat;

		blk_mq_freeze_queue(blkg->q);

		if (enable == 1)
			atomic_inc(&blkiolat->enabled);
		else if (enable == -1)
			atomic_dec(&blkiolat->enabled);
		else
			WARN_ON_ONCE(1);

		blk_mq_unfreeze_queue(blkg->q);

		blkg_put(blkg);
		blk_put_queue(blkg->q);
	}
	return ret ?: nbytes;
}