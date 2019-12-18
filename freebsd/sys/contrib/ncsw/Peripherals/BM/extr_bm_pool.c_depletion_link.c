#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_BmPortalLow; TYPE_2__** depletionPoolsTable; } ;
typedef  TYPE_1__ t_BmPortal ;
struct TYPE_7__ {size_t bpid; scalar_t__ h_BmPortal; } ;
typedef  TYPE_2__ t_BmPool ;

/* Variables and functions */
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bm_isr_bscn_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void depletion_link(t_BmPool *p_BmPool)
{
    t_BmPortal *p_Portal = (t_BmPortal *)p_BmPool->h_BmPortal;

    NCSW_PLOCK(p_Portal);
    p_Portal->depletionPoolsTable[p_BmPool->bpid] = p_BmPool;
    bm_isr_bscn_mask(p_Portal->p_BmPortalLow, (uint8_t)p_BmPool->bpid, 1);
    PUNLOCK(p_Portal);
}