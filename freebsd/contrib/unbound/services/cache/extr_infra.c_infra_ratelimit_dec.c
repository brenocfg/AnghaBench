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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct lruhash_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  data; } ;
struct infra_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  infra_dp_ratelimit ; 
 struct lruhash_entry* infra_find_ratedata (struct infra_cache*,int /*<<< orphan*/ *,size_t,int) ; 
 int* infra_rate_find_second (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

void infra_ratelimit_dec(struct infra_cache* infra, uint8_t* name,
	size_t namelen, time_t timenow)
{
	struct lruhash_entry* entry;
	int* cur;
	if(!infra_dp_ratelimit)
		return; /* not enabled */
	entry = infra_find_ratedata(infra, name, namelen, 1);
	if(!entry) return; /* not cached */
	cur = infra_rate_find_second(entry->data, timenow);
	if((*cur) > 0)
		(*cur)--;
	lock_rw_unlock(&entry->lock);
}