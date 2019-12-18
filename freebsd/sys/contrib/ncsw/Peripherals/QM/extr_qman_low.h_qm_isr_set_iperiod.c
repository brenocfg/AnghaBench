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
typedef  int /*<<< orphan*/  uint16_t ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITPR ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qm_isr_set_iperiod(struct qm_portal *portal, uint16_t iperiod)
{
    qm_out(ITPR, iperiod);
}