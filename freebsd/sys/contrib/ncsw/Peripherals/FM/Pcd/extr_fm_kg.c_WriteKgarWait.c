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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* p_FmPcdKg; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct fman_kg_regs {int dummy; } ;
struct TYPE_4__ {struct fman_kg_regs* p_FmPcdKgRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fman_kg_write_ar_wait (struct fman_kg_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error WriteKgarWait(t_FmPcd *p_FmPcd, uint32_t fmkg_ar)
{

    struct fman_kg_regs *regs = p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs;

    if (fman_kg_write_ar_wait(regs, fmkg_ar))
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("Keygen scheme access violation"));

    return E_OK;
}