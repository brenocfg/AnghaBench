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
struct delegpt_ns {size_t namelen; struct delegpt_ns* next; int /*<<< orphan*/  name; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct delegpt_ns*
delegpt_find_ns(struct delegpt* dp, uint8_t* name, size_t namelen)
{
	struct delegpt_ns* p = dp->nslist;
	while(p) {
		if(namelen == p->namelen && 
			query_dname_compare(name, p->name) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}