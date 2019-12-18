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
typedef  int uint8_t ;
struct TYPE_2__ {int bound; } ;
struct qm_portal {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 

__attribute__((used)) static __inline__ void __qm_portal_unbind(struct qm_portal *portal, uint8_t iface)
{
#ifdef QM_CHECKING
    ASSERT_COND(portal->config.bound & iface);
#endif /* QM_CHECKING */
    portal->config.bound &= ~iface;
}