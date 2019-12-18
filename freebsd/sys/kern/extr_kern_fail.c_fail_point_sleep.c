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
struct fail_point {int fp_flags; int /*<<< orphan*/  fp_post_sleep_arg; int /*<<< orphan*/  (* fp_post_sleep_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  fp_pre_sleep_arg; int /*<<< orphan*/  (* fp_pre_sleep_fn ) (int /*<<< orphan*/ ) ;} ;
typedef  int int64_t ;
typedef  enum fail_point_return_code { ____Placeholder_fail_point_return_code } fail_point_return_code ;

/* Variables and functions */
 int FAIL_POINT_RC_QUEUED ; 
 int FAIL_POINT_USE_TIMEOUT_PATH ; 
 int /*<<< orphan*/  FP_SLEEP_CHANNEL (struct fail_point*) ; 
 int /*<<< orphan*/  PWAIT ; 
 int howmany (int,long) ; 
 int hz ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void
fail_point_sleep(struct fail_point *fp, int msecs,
        enum fail_point_return_code *pret)
{
	int timo;

	/* Convert from millisecs to ticks, rounding up */
	timo = howmany((int64_t)msecs * hz, 1000L);

	if (timo > 0) {
		if (!(fp->fp_flags & FAIL_POINT_USE_TIMEOUT_PATH)) {
			if (fp->fp_pre_sleep_fn)
				fp->fp_pre_sleep_fn(fp->fp_pre_sleep_arg);

			tsleep(FP_SLEEP_CHANNEL(fp), PWAIT, "failpt", timo);

			if (fp->fp_post_sleep_fn)
				fp->fp_post_sleep_fn(fp->fp_post_sleep_arg);
		} else {
			if (fp->fp_pre_sleep_fn)
				fp->fp_pre_sleep_fn(fp->fp_pre_sleep_arg);

			timeout(fp->fp_post_sleep_fn, fp->fp_post_sleep_arg,
			    timo);
			*pret = FAIL_POINT_RC_QUEUED;
		}
	}
}