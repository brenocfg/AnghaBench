#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_BIND_ISR ; 
 int /*<<< orphan*/  __qm_portal_unbind (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qm_isr_finish(struct qm_portal *portal)
{
    __qm_portal_unbind(portal, QM_BIND_ISR);
}