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
typedef  int /*<<< orphan*/  uint32_t ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQRR_SDQCR ; 
 int /*<<< orphan*/  qm_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint32_t qm_dqrr_sdqcr_get(struct qm_portal *portal)
{
    return qm_in(DQRR_SDQCR);
}