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
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_5__ {struct TYPE_5__* p_DtsecDriverParam; } ;
typedef  TYPE_1__ t_Dtsec ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FreeInitResources (TYPE_1__*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 

__attribute__((used)) static t_Error DtsecFree(t_Handle h_Dtsec)
{
    t_Dtsec      *p_Dtsec = (t_Dtsec *)h_Dtsec;

    SANITY_CHECK_RETURN_ERROR(p_Dtsec, E_INVALID_HANDLE);

    if (p_Dtsec->p_DtsecDriverParam)
    {
        /* Called after config */
        XX_Free(p_Dtsec->p_DtsecDriverParam);
        p_Dtsec->p_DtsecDriverParam = NULL;
    }
    else
        /* Called after init */
        FreeInitResources(p_Dtsec);

    XX_Free(p_Dtsec);

    return E_OK;
}