#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {scalar_t__ h_Mem; } ;
typedef  TYPE_1__ t_FmMuram ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MM_Free (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (scalar_t__) ; 

t_Error FM_MURAM_Free(t_Handle h_FmMuram)
{
    t_FmMuram   *p_FmMuram = ( t_FmMuram *)h_FmMuram;

    if (p_FmMuram->h_Mem)
        MM_Free(p_FmMuram->h_Mem);

    XX_Free(h_FmMuram);

    return E_OK;
}