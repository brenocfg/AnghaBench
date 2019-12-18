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
struct rrset_ref {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static int
reply_info_sortref_cmp(const void* a, const void* b)
{
	struct rrset_ref* x = (struct rrset_ref*)a;
	struct rrset_ref* y = (struct rrset_ref*)b;
	if(x->key < y->key) return -1;
	if(x->key > y->key) return 1;
	return 0;
}