#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mc_gs; int /*<<< orphan*/  mc_fs; } ;
struct TYPE_5__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct reg {int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
pt_reg_to_ucontext(const struct reg *r, ucontext_t *uc)
{
	memcpy(&uc->uc_mcontext.mc_fs, &r->r_fs, 18*4);
	uc->uc_mcontext.mc_gs = r->r_gs;
}