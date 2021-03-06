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
struct TYPE_3__ {int /*<<< orphan*/  numOfRxSc; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  f_Exception; } ;
typedef  TYPE_1__ t_FmMacsecSecY ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error CheckFmMacsecSecYParameters(t_FmMacsecSecY *p_FmMacsecSecY)
{
    if (!p_FmMacsecSecY->f_Exception)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Exceptions callback not provided"));

    if (!p_FmMacsecSecY->f_Event)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Events callback not provided"));

    if (!p_FmMacsecSecY->numOfRxSc)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Num of Rx Scs must be greater than '0'"));


    return E_OK;
}