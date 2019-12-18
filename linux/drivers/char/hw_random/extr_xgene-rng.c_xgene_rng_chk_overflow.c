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
typedef  int u32 ;
struct xgene_rng_dev {int failure_cnt; scalar_t__ csr_base; void* failure_ts; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int LONG_RUN_FAIL_MASK ; 
 int MONOBIT_FAIL_MASK ; 
 int NOISE_FAIL_MASK ; 
 int POKER_FAIL_MASK ; 
 scalar_t__ RNG_ALARMSTOP ; 
 scalar_t__ RNG_INTR_STS_ACK ; 
 int RUN_FAIL_MASK ; 
 int SHUTDOWN_OFLO_MASK ; 
 int STUCK_OUT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* jiffies ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (void*,void*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xgene_rng_init_fro (struct xgene_rng_dev*,int) ; 
 int /*<<< orphan*/  xgene_rng_start_timer (struct xgene_rng_dev*) ; 

__attribute__((used)) static void xgene_rng_chk_overflow(struct xgene_rng_dev *ctx)
{
	u32 val;

	val = readl(ctx->csr_base + RNG_INTR_STS_ACK);
	if (val & MONOBIT_FAIL_MASK)
		/*
		 * LFSR detected an out-of-bounds number of 1s after
		 * checking 20,000 bits (test T1 as specified in the
		 * AIS-31 standard)
		 */
		dev_err(ctx->dev, "test monobit failure error 0x%08X\n", val);
	if (val & POKER_FAIL_MASK)
		/*
		 * LFSR detected an out-of-bounds value in at least one
		 * of the 16 poker_count_X counters or an out of bounds sum
		 * of squares value after checking 20,000 bits (test T2 as
		 * specified in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test poker failure error 0x%08X\n", val);
	if (val & LONG_RUN_FAIL_MASK)
		/*
		 * LFSR detected a sequence of 34 identical bits
		 * (test T4 as specified in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test long run failure error 0x%08X\n", val);
	if (val & RUN_FAIL_MASK)
		/*
		 * LFSR detected an outof-bounds value for at least one
		 * of the running counters after checking 20,000 bits
		 * (test T3 as specified in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test run failure error 0x%08X\n", val);
	if (val & NOISE_FAIL_MASK)
		/* LFSR detected a sequence of 48 identical bits */
		dev_err(ctx->dev, "noise failure error 0x%08X\n", val);
	if (val & STUCK_OUT_MASK)
		/*
		 * Detected output data registers generated same value twice
		 * in a row
		 */
		dev_err(ctx->dev, "stuck out failure error 0x%08X\n", val);

	if (val & SHUTDOWN_OFLO_MASK) {
		u32 frostopped;

		/* FROs shut down after a second error event. Try recover. */
		if (++ctx->failure_cnt == 1) {
			/* 1st time, just recover */
			ctx->failure_ts = jiffies;
			frostopped = readl(ctx->csr_base + RNG_ALARMSTOP);
			xgene_rng_init_fro(ctx, frostopped);

			/*
			 * We must start a timer to clear out this error
			 * in case the system timer wrap around
			 */
			xgene_rng_start_timer(ctx);
		} else {
			/* 2nd time failure in lesser than 1 minute? */
			if (time_after(ctx->failure_ts + 60 * HZ, jiffies)) {
				dev_err(ctx->dev,
					"FRO shutdown failure error 0x%08X\n",
					val);
			} else {
				/* 2nd time failure after 1 minutes, recover */
				ctx->failure_ts = jiffies;
				ctx->failure_cnt = 1;
				/*
				 * We must start a timer to clear out this
				 * error in case the system timer wrap
				 * around
				 */
				xgene_rng_start_timer(ctx);
			}
			frostopped = readl(ctx->csr_base + RNG_ALARMSTOP);
			xgene_rng_init_fro(ctx, frostopped);
		}
	}
	/* Clear them all */
	writel(val, ctx->csr_base + RNG_INTR_STS_ACK);
}