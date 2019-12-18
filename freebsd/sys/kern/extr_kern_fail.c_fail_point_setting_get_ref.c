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
struct fail_point {struct fail_point_setting* fp_setting; int /*<<< orphan*/  fp_ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_acq_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct fail_point_setting *
fail_point_setting_get_ref(struct fail_point *fp)
{
	struct fail_point_setting *fp_setting;

	/* Invariant: if we have a ref, our pointer to fp_setting is safe */
	atomic_add_acq_32(&fp->fp_ref_cnt, 1);
	fp_setting = fp->fp_setting;

	return (fp_setting);
}