#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* p_QmRegs; } ;
typedef  TYPE_2__ t_Qm ;
typedef  size_t e_QmWqClass ;
struct TYPE_5__ {int /*<<< orphan*/ * wq_cs_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void QmSetWqScheduling(t_Qm *p_Qm,
                                         e_QmWqClass wqClass,
                                         uint8_t csElev,
                                         uint8_t csw2,
                                         uint8_t csw3,
                                         uint8_t csw4,
                                         uint8_t csw5,
                                         uint8_t csw6,
                                         uint8_t csw7)
{
    ASSERT_COND(p_Qm);

    WRITE_UINT32(p_Qm->p_QmRegs->wq_cs_cfg[wqClass],
                 (uint32_t)(((csElev & 0xff) << 24) |
                 ((csw2 & 0x7) << 20) |
                 ((csw3 & 0x7) << 16) |
                 ((csw4 & 0x7) << 12) |
                 ((csw5 & 0x7) << 8) |
                 ((csw6 & 0x7) << 4) |
                 (csw7 & 0x7)));
}