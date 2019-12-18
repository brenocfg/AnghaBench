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
struct fail_point {int /*<<< orphan*/  fp_ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_subtract_rel_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
fail_point_setting_release_ref(struct fail_point *fp)
{

	KASSERT(&fp->fp_ref_cnt > 0, ("Attempting to deref w/no refs"));
	atomic_subtract_rel_32(&fp->fp_ref_cnt, 1);
}