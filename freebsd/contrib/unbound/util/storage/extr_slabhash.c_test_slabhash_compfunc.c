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
struct slabhash_testkey {scalar_t__ id; } ;

/* Variables and functions */

int test_slabhash_compfunc(void* key1, void* key2)
{
	struct slabhash_testkey* k1 = (struct slabhash_testkey*)key1;
	struct slabhash_testkey* k2 = (struct slabhash_testkey*)key2;
	if(k1->id == k2->id)
		return 0;
	if(k1->id > k2->id)
		return 1;
	return -1;
}