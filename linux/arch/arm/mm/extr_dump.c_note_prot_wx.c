#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pg_state {int current_prot; size_t level; unsigned long start_address; unsigned long wx_pages; int /*<<< orphan*/  check_wx; } ;
struct TYPE_6__ {TYPE_2__* nx_bit; TYPE_1__* ro_bit; } ;
struct TYPE_5__ {int mask; int val; } ;
struct TYPE_4__ {int mask; int val; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,void*) ; 
 TYPE_3__* pg_level ; 

__attribute__((used)) static void note_prot_wx(struct pg_state *st, unsigned long addr)
{
	if (!st->check_wx)
		return;
	if ((st->current_prot & pg_level[st->level].ro_bit->mask) ==
				pg_level[st->level].ro_bit->val)
		return;
	if ((st->current_prot & pg_level[st->level].nx_bit->mask) ==
				pg_level[st->level].nx_bit->val)
		return;

	WARN_ONCE(1, "arm/mm: Found insecure W+X mapping at address %pS\n",
			(void *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
}