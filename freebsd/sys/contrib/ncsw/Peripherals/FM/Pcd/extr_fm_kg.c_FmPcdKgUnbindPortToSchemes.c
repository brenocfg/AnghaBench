#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {int /*<<< orphan*/  hardwarePortId; } ;
typedef  TYPE_1__ t_FmPcdKgInterModuleBindPortToSchemes ;
typedef  int /*<<< orphan*/  t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DecSchemeOwners (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FmPcdKgBuildBindPortToSchemes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ KgWriteSp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

t_Error FmPcdKgUnbindPortToSchemes(t_Handle h_FmPcd, t_FmPcdKgInterModuleBindPortToSchemes *p_SchemeBind)
{
    t_FmPcd                 *p_FmPcd = (t_FmPcd*)h_FmPcd;
    uint32_t                spReg;
    t_Error                 err = E_OK;

    err = FmPcdKgBuildBindPortToSchemes(p_FmPcd, p_SchemeBind, &spReg, FALSE);
    if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);

    err = KgWriteSp(p_FmPcd, p_SchemeBind->hardwarePortId, spReg, FALSE);
    if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);

    DecSchemeOwners(p_FmPcd, p_SchemeBind);

    return E_OK;
}