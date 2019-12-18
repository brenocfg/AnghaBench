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

__attribute__((used)) static struct fail_point_setting *
fail_point_swap_settings(struct fail_point *fp,
        struct fail_point_setting *fp_setting_new)
{
	struct fail_point_setting *fp_setting_old;

	fp_setting_old = fp->fp_setting;
	fp->fp_setting = fp_setting_new;

	return (fp_setting_old);
}