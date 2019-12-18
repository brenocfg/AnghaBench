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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int pkey_access_permitted (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pkey_disabled ; 
 int /*<<< orphan*/  pte_to_pkey_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 

bool arch_pte_access_permitted(u64 pte, bool write, bool execute)
{
	if (static_branch_likely(&pkey_disabled))
		return true;

	return pkey_access_permitted(pte_to_pkey_bits(pte), write, execute);
}