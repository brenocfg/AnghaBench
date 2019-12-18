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
typedef  int uint8_t ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int QM_DQRR_SIZE ; 
 int qm_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void qm_dqrr_set_maxfill(struct qm_portal *portal, uint8_t mf)
{
    qm_out(CFG, (qm_in(CFG) & 0xff0fffff) |
        ((mf & (QM_DQRR_SIZE - 1)) << 20));
}