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
typedef  scalar_t__ u_long ;
struct pmap_invl_gen {scalar_t__ gen; } ;
struct TYPE_6__ {scalar_t__ gen; } ;
struct TYPE_4__ {struct pmap_invl_gen md_invl_gen; } ;
struct TYPE_5__ {TYPE_1__ td_md; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmap_invl_gen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_ASSERT_NOT_IN_DI () ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  invl_gen_mtx ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pmap_invl_gen ; 
 int /*<<< orphan*/  pmap_invl_gen_tracker ; 

__attribute__((used)) static void
pmap_delayed_invl_start_l(void)
{
	struct pmap_invl_gen *invl_gen;
	u_long currgen;

	invl_gen = &curthread->td_md.md_invl_gen;
	PMAP_ASSERT_NOT_IN_DI();
	mtx_lock(&invl_gen_mtx);
	if (LIST_EMPTY(&pmap_invl_gen_tracker))
		currgen = pmap_invl_gen;
	else
		currgen = LIST_FIRST(&pmap_invl_gen_tracker)->gen;
	invl_gen->gen = currgen + 1;
	LIST_INSERT_HEAD(&pmap_invl_gen_tracker, invl_gen, link);
	mtx_unlock(&invl_gen_mtx);
}