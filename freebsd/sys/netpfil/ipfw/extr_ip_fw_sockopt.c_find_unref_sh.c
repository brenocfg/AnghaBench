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
struct ipfw_sopt_handler {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  version; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL3_LOCK () ; 
 int /*<<< orphan*/  CTL3_UNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ctl3_refct ; 
 struct ipfw_sopt_handler* find_sh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
find_unref_sh(struct ipfw_sopt_handler *psh)
{
	struct ipfw_sopt_handler *sh;

	CTL3_LOCK();
	sh = find_sh(psh->opcode, psh->version, NULL);
	KASSERT(sh != NULL, ("ctl3 handler disappeared"));
	sh->refcnt--;
	ctl3_refct--;
	CTL3_UNLOCK();
}