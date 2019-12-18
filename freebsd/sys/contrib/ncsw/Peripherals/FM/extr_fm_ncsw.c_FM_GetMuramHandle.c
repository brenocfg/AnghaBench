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
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {scalar_t__ h_FmMuram; } ;
typedef  TYPE_1__ t_Fm ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

t_Handle FM_GetMuramHandle(t_Handle h_Fm)
{
    t_Fm        *p_Fm = (t_Fm*)h_Fm;

    SANITY_CHECK_RETURN_VALUE(p_Fm, E_INVALID_HANDLE, NULL);

    return (p_Fm->h_FmMuram);
}