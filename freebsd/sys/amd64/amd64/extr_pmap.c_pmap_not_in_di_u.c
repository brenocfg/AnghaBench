#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmap_invl_gen {scalar_t__ next; } ;
struct TYPE_3__ {struct pmap_invl_gen md_invl_gen; } ;
struct TYPE_4__ {TYPE_1__ td_md; } ;

/* Variables and functions */
 uintptr_t PMAP_INVL_GEN_NEXT_INVALID ; 
 TYPE_2__* curthread ; 

__attribute__((used)) static bool
pmap_not_in_di_u(void)
{
	struct pmap_invl_gen *invl_gen;

	invl_gen = &curthread->td_md.md_invl_gen;
	return (((uintptr_t)invl_gen->next & PMAP_INVL_GEN_NEXT_INVALID) != 0);
}