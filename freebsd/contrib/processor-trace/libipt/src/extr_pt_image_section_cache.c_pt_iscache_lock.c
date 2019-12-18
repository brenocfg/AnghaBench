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
struct pt_image_section_cache {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int mtx_lock (int /*<<< orphan*/ *) ; 
 int pte_bad_lock ; 
 int pte_internal ; 
 int thrd_success ; 

__attribute__((used)) static inline int pt_iscache_lock(struct pt_image_section_cache *iscache)
{
	if (!iscache)
		return -pte_internal;

#if defined(FEATURE_THREADS)
	{
		int errcode;

		errcode = mtx_lock(&iscache->lock);
		if (errcode != thrd_success)
			return -pte_bad_lock;
	}
#endif /* defined(FEATURE_THREADS) */

	return 0;
}