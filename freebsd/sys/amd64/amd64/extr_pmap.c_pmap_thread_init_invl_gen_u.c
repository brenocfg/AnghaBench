#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmap_invl_gen {void* next; scalar_t__ gen; } ;
struct TYPE_2__ {struct pmap_invl_gen md_invl_gen; } ;
struct thread {TYPE_1__ td_md; } ;

/* Variables and functions */
 scalar_t__ PMAP_INVL_GEN_NEXT_INVALID ; 

__attribute__((used)) static void
pmap_thread_init_invl_gen_u(struct thread *td)
{
	struct pmap_invl_gen *invl_gen;

	invl_gen = &td->td_md.md_invl_gen;
	invl_gen->gen = 0;
	invl_gen->next = (void *)PMAP_INVL_GEN_NEXT_INVALID;
}