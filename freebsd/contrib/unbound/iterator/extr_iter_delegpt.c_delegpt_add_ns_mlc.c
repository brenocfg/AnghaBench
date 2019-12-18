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
typedef  scalar_t__ uint8_t ;
struct delegpt_ns {size_t namelen; scalar_t__ done_pside6; scalar_t__ done_pside4; scalar_t__ lame; scalar_t__ got6; scalar_t__ got4; scalar_t__ resolved; struct delegpt_ns* next; int /*<<< orphan*/  name; } ;
struct delegpt {struct delegpt_ns* nslist; int /*<<< orphan*/  dp_type_mlc; } ;

/* Variables and functions */
 scalar_t__ delegpt_find_ns (struct delegpt*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  dname_count_size_labels (scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  free (struct delegpt_ns*) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memdup (scalar_t__*,size_t) ; 

int delegpt_add_ns_mlc(struct delegpt* dp, uint8_t* name, uint8_t lame)
{
	struct delegpt_ns* ns;
	size_t len;
	(void)dname_count_size_labels(name, &len);
	log_assert(dp->dp_type_mlc);
	/* slow check for duplicates to avoid counting failures when
	 * adding the same server as a dependency twice */
	if(delegpt_find_ns(dp, name, len))
		return 1;
	ns = (struct delegpt_ns*)malloc(sizeof(struct delegpt_ns));
	if(!ns)
		return 0;
	ns->namelen = len;
	ns->name = memdup(name, ns->namelen);
	if(!ns->name) {
		free(ns);
		return 0;
	}
	ns->next = dp->nslist;
	dp->nslist = ns;
	ns->resolved = 0;
	ns->got4 = 0;
	ns->got6 = 0;
	ns->lame = (uint8_t)lame;
	ns->done_pside4 = 0;
	ns->done_pside6 = 0;
	return 1;
}