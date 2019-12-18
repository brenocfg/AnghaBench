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
struct rrset_cache {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  slabhash_delete (int /*<<< orphan*/ *) ; 

void rrset_cache_delete(struct rrset_cache* r)
{
	if(!r) 
		return;
	slabhash_delete(&r->table);
	/* slabhash delete also does free(r), since table is first in struct*/
}