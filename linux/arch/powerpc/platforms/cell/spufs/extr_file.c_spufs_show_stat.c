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
struct TYPE_2__ {size_t util_state; int /*<<< orphan*/  libassist; int /*<<< orphan*/  maj_flt; int /*<<< orphan*/  min_flt; int /*<<< orphan*/  hash_flt; int /*<<< orphan*/  invol_ctx_switch; int /*<<< orphan*/  vol_ctx_switch; } ;
struct spu_context {TYPE_1__ stats; } ;
struct seq_file {struct spu_context* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_UTIL_IDLE_LOADED ; 
 int /*<<< orphan*/  SPU_UTIL_IOWAIT ; 
 int /*<<< orphan*/  SPU_UTIL_SYSTEM ; 
 int /*<<< orphan*/  SPU_UTIL_USER ; 
 int /*<<< orphan*/ * ctx_state_names ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  spufs_acct_time (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_class2_intrs (struct spu_context*) ; 
 int /*<<< orphan*/  spufs_slb_flts (struct spu_context*) ; 

__attribute__((used)) static int spufs_show_stat(struct seq_file *s, void *private)
{
	struct spu_context *ctx = s->private;
	int ret;

	ret = spu_acquire(ctx);
	if (ret)
		return ret;

	seq_printf(s, "%s %llu %llu %llu %llu "
		      "%llu %llu %llu %llu %llu %llu %llu %llu\n",
		ctx_state_names[ctx->stats.util_state],
		spufs_acct_time(ctx, SPU_UTIL_USER),
		spufs_acct_time(ctx, SPU_UTIL_SYSTEM),
		spufs_acct_time(ctx, SPU_UTIL_IOWAIT),
		spufs_acct_time(ctx, SPU_UTIL_IDLE_LOADED),
		ctx->stats.vol_ctx_switch,
		ctx->stats.invol_ctx_switch,
		spufs_slb_flts(ctx),
		ctx->stats.hash_flt,
		ctx->stats.min_flt,
		ctx->stats.maj_flt,
		spufs_class2_intrs(ctx),
		ctx->stats.libassist);
	spu_release(ctx);
	return 0;
}