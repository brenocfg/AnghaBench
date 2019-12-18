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
struct regional {int dummy; } ;
struct delegpt_ns {size_t namelen; scalar_t__ name; scalar_t__ done_pside6; scalar_t__ done_pside4; int /*<<< orphan*/  lame; scalar_t__ got6; scalar_t__ got4; scalar_t__ resolved; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; int /*<<< orphan*/  dp_type_mlc; } ;

/* Variables and functions */
 scalar_t__ delegpt_find_ns (struct delegpt*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 
 scalar_t__ regional_alloc_init (struct regional*,int /*<<< orphan*/ *,size_t) ; 

int 
delegpt_add_ns(struct delegpt* dp, struct regional* region, uint8_t* name,
	uint8_t lame)
{
	struct delegpt_ns* ns;
	size_t len;
	(void)dname_count_size_labels(name, &len);
	log_assert(!dp->dp_type_mlc);
	/* slow check for duplicates to avoid counting failures when
	 * adding the same server as a dependency twice */
	if(delegpt_find_ns(dp, name, len))
		return 1;
	ns = (struct delegpt_ns*)regional_alloc(region,
		sizeof(struct delegpt_ns));
	if(!ns)
		return 0;
	ns->next = dp->nslist;
	ns->namelen = len;
	dp->nslist = ns;
	ns->name = regional_alloc_init(region, name, ns->namelen);
	ns->resolved = 0;
	ns->got4 = 0;
	ns->got6 = 0;
	ns->lame = lame;
	ns->done_pside4 = 0;
	ns->done_pside6 = 0;
	return ns->name != 0;
}