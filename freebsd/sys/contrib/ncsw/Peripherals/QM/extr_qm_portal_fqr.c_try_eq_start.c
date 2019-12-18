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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_LowQmPortal; } ;
typedef  TYPE_1__ t_QmPortal ;
struct qm_eqcr_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ EQCR_THRESH ; 
 int /*<<< orphan*/  qmPortalEqcrCcePrefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmPortalEqcrCceUpdate (int /*<<< orphan*/ ) ; 
 scalar_t__ qm_eqcr_get_avail (int /*<<< orphan*/ ) ; 
 struct qm_eqcr_entry* qm_eqcr_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct qm_eqcr_entry *try_eq_start(t_QmPortal *p_QmPortal)
{
    struct qm_eqcr_entry    *p_Eq;
    uint8_t                 avail;

    avail = qm_eqcr_get_avail(p_QmPortal->p_LowQmPortal);
    if (avail == EQCR_THRESH)
        qmPortalEqcrCcePrefetch(p_QmPortal->p_LowQmPortal);
    else if (avail < EQCR_THRESH)
            qmPortalEqcrCceUpdate(p_QmPortal->p_LowQmPortal);
    p_Eq = qm_eqcr_start(p_QmPortal->p_LowQmPortal);

    return p_Eq;
}