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
struct TYPE_5__ {int /*<<< orphan*/  mc_frame; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct reg {int dummy; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct reg const*,int /*<<< orphan*/ ) ; 

void
pt_reg_to_ucontext(const struct reg *r, ucontext_t *uc)
{
	mcontext_t *mc = &uc->uc_mcontext;

	memcpy(mc->mc_frame, r, MIN(sizeof(mc->mc_frame), sizeof(*r)));
}