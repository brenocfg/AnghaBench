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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_ASIC_RESET ; 
 int /*<<< orphan*/  WRITE_OFFSET32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void qla_hw_reset(qla_host_t *ha)
{
        WRITE_OFFSET32(ha, Q8_ASIC_RESET, 0xFFFFFFFF);
}