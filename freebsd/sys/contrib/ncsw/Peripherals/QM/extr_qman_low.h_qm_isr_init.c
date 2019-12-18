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
typedef  int /*<<< orphan*/  t_Error ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  QM_BIND_ISR ; 
 scalar_t__ __qm_portal_bind (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ t_Error qm_isr_init(struct qm_portal *portal)
{
    if (__qm_portal_bind(portal, QM_BIND_ISR))
        return ERROR_CODE(E_BUSY);
    return E_OK;
}