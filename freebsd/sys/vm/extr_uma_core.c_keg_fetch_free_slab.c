#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * uma_slab_t ;
typedef  TYPE_1__* uma_keg_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ uk_reserve; scalar_t__ uk_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEG_LOCK_ASSERT (TYPE_1__*) ; 
 int M_USE_RESERVE ; 
 int /*<<< orphan*/ * keg_first_slab (TYPE_1__*,int,int) ; 

__attribute__((used)) static uma_slab_t
keg_fetch_free_slab(uma_keg_t keg, int domain, bool rr, int flags)
{
	uint32_t reserve;

	KEG_LOCK_ASSERT(keg);

	reserve = (flags & M_USE_RESERVE) != 0 ? 0 : keg->uk_reserve;
	if (keg->uk_free <= reserve)
		return (NULL);
	return (keg_first_slab(keg, domain, rr));
}