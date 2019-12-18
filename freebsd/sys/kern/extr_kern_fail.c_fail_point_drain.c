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
struct fail_point_setting {int dummy; } ;
struct fail_point {int fp_ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_PAUSE_CHANNEL (struct fail_point*) ; 
 int /*<<< orphan*/  PWAIT ; 
 struct fail_point_setting* fail_point_swap_settings (struct fail_point*,struct fail_point_setting*) ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (struct fail_point**,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fail_point_drain(struct fail_point *fp, int expected_ref)
{
	struct fail_point_setting *entries;

	entries = fail_point_swap_settings(fp, NULL);
	/**
	 * We have unpaused all threads; so we will wait no longer
	 * than the time taken for the longest remaining sleep, or
	 * the length of time of a long-running code block.
	 */
	while (fp->fp_ref_cnt > expected_ref) {
		wakeup(FP_PAUSE_CHANNEL(fp));
		tsleep(&fp, PWAIT, "fail_point_drain", hz / 100);
	}
	fail_point_swap_settings(fp, entries);
}