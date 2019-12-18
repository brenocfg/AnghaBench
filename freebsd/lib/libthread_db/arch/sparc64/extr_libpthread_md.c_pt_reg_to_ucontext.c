#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct reg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct reg const*,int /*<<< orphan*/ ) ; 

void
pt_reg_to_ucontext(const struct reg *r, ucontext_t *uc)
{

	memcpy(&uc->uc_mcontext, r, MIN(sizeof(uc->uc_mcontext), sizeof(*r)));
}