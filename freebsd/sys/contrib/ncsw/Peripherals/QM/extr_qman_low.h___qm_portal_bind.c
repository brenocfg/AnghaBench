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
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_2__ {int bound; } ;
struct qm_portal {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 

__attribute__((used)) static __inline__ t_Error __qm_portal_bind(struct qm_portal *portal, uint8_t iface)
{
    t_Error ret = E_BUSY;
    if (!(portal->config.bound & iface)) {
        portal->config.bound |= iface;
        ret = E_OK;
    }
    return ret;
}