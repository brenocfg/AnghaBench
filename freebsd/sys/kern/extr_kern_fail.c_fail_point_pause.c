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
struct mtx {int dummy; } ;
struct fail_point {int /*<<< orphan*/  fp_post_sleep_arg; int /*<<< orphan*/  (* fp_post_sleep_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  fp_pre_sleep_arg; int /*<<< orphan*/  (* fp_pre_sleep_fn ) (int /*<<< orphan*/ ) ;} ;
typedef  enum fail_point_return_code { ____Placeholder_fail_point_return_code } fail_point_return_code ;

/* Variables and functions */
 int /*<<< orphan*/  FP_PAUSE_CHANNEL (struct fail_point*) ; 
 int /*<<< orphan*/  msleep_spin (int /*<<< orphan*/ ,struct mtx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fail_point_pause(struct fail_point *fp, enum fail_point_return_code *pret,
        struct mtx *mtx_sleep)
{

	if (fp->fp_pre_sleep_fn)
		fp->fp_pre_sleep_fn(fp->fp_pre_sleep_arg);

	msleep_spin(FP_PAUSE_CHANNEL(fp), mtx_sleep, "failpt", 0);

	if (fp->fp_post_sleep_fn)
		fp->fp_post_sleep_fn(fp->fp_post_sleep_arg);
}