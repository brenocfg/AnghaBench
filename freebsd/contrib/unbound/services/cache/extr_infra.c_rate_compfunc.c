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
struct rate_key {scalar_t__ namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
rate_compfunc(void* key1, void* key2)
{
	struct rate_key* k1 = (struct rate_key*)key1;
	struct rate_key* k2 = (struct rate_key*)key2;
	if(k1->namelen != k2->namelen) {
		if(k1->namelen < k2->namelen)
			return -1;
		return 1;
	}
	return query_dname_compare(k1->name, k2->name);
}