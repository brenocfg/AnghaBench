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
 struct lruhash_entry* infra_find_ratedata (struct infra_cache*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int infra_find_ratelimit (struct infra_cache*,int /*<<< orphan*/ *,size_t) ; 
 int infra_rate_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

int infra_ratelimit_exceeded(struct infra_cache* infra, uint8_t* name,
	size_t namelen, time_t timenow)
{
	struct lruhash_entry* entry;
	int lim, max;
	if(!infra_dp_ratelimit)
		return 0; /* not enabled */

	/* find ratelimit */
	lim = infra_find_ratelimit(infra, name, namelen);
	if(!lim)
		return 0; /* disabled for this domain */

	/* find current rate */
	entry = infra_find_ratedata(infra, name, namelen, 0);
	if(!entry)
		return 0; /* not cached */
	max = infra_rate_max(entry->data, timenow);
	lock_rw_unlock(&entry->lock);

	return (max >= lim);
}