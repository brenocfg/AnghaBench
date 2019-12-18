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
struct TYPE_5__ {int /*<<< orphan*/  p_BmPortalLow; TYPE_1__* cbs; } ;
typedef  TYPE_2__ t_BmPortal ;
typedef  size_t bmRingType_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* f_BmPrefetchCb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void BmPrefetch(t_BmPortal *p_BmPortal, bmRingType_t type)
{
    if (p_BmPortal->cbs[type].f_BmPrefetchCb)
        p_BmPortal->cbs[type].f_BmPrefetchCb(p_BmPortal->p_BmPortalLow);
}