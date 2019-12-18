#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ dataSize; scalar_t__ h_NextManip; struct TYPE_6__* h_PrevManip; } ;
typedef  TYPE_1__ t_FmPcdManip ;

/* Variables and functions */
 int /*<<< orphan*/  MANIP_IS_UNIFIED (TYPE_1__*) ; 
 scalar_t__ MANIP_IS_UNIFIED_NON_FIRST (TYPE_1__*) ; 
 scalar_t__ MANIP_IS_UNIFIED_NON_LAST (TYPE_1__*) ; 

__attribute__((used)) static uint16_t GetDataSize(t_FmPcdManip *p_Manip)
{
    uint16_t size = 0;
    t_FmPcdManip *p_CurManip = p_Manip;

    if (!MANIP_IS_UNIFIED(p_Manip))
        return p_Manip->dataSize;

    /* accumulate sizes, starting with the first node */
    while (MANIP_IS_UNIFIED_NON_FIRST(p_CurManip))
        p_CurManip = p_CurManip->h_PrevManip;

    while (MANIP_IS_UNIFIED_NON_LAST(p_CurManip))
    {
        size += p_CurManip->dataSize;
        p_CurManip = (t_FmPcdManip *)p_CurManip->h_NextManip;
    }
    size += p_CurManip->dataSize; /* add last size */

    return (size);
}