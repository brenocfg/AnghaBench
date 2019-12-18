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

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fail_point_setting*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_setting_garbage ; 
 int /*<<< orphan*/  fs_garbage_link ; 
 int /*<<< orphan*/  mtx_garbage_list ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fail_point_setting_garbage_append(struct fail_point_setting *fp_setting)
{

	mtx_lock_spin(&mtx_garbage_list);
	STAILQ_INSERT_TAIL(&fp_setting_garbage, fp_setting,
	        fs_garbage_link);
	mtx_unlock_spin(&mtx_garbage_list);
}