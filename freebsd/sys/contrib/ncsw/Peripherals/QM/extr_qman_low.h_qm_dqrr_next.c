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
typedef  int /*<<< orphan*/  uint8_t ;
struct qm_dqrr {int /*<<< orphan*/  fill; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQRR_INC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint8_t qm_dqrr_next(struct qm_portal *portal)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->fill);
#endif
    dqrr->cursor = DQRR_INC(dqrr->cursor);
    return --dqrr->fill;
}