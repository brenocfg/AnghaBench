#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  info; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ sthyi_cache ; 
 int sthyi_init_cache () ; 
 int /*<<< orphan*/  sthyi_mutex ; 
 int sthyi_update_cache (scalar_t__*) ; 
 scalar_t__ time_is_before_jiffies (int /*<<< orphan*/ ) ; 

int sthyi_fill(void *dst, u64 *rc)
{
	int r;

	mutex_lock(&sthyi_mutex);
	r = sthyi_init_cache();
	if (r)
		goto out;

	if (time_is_before_jiffies(sthyi_cache.end)) {
		/* cache expired */
		r = sthyi_update_cache(rc);
		if (r)
			goto out;
	}
	*rc = 0;
	memcpy(dst, sthyi_cache.info, PAGE_SIZE);
out:
	mutex_unlock(&sthyi_mutex);
	return r;
}