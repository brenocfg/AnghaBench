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
struct fail_point {struct fail_point_setting* fp_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  fail_point_swap_settings (struct fail_point*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fail_point_eval_swap_out(struct fail_point *fp,
        struct fail_point_setting *fp_setting)
{

	/* We may have already been swapped out and replaced; ignore. */
	if (fp->fp_setting == fp_setting)
		fail_point_swap_settings(fp, NULL);
}