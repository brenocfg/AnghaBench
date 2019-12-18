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
struct uml_pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  get_regs_from_mc (struct uml_pt_regs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct uml_pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uml_pt_regs*) ; 

__attribute__((used)) static void timer_real_alarm_handler(mcontext_t *mc)
{
	struct uml_pt_regs regs;

	if (mc != NULL)
		get_regs_from_mc(&regs, mc);
	else
		memset(&regs, 0, sizeof(regs));
	timer_handler(SIGALRM, NULL, &regs);
}