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
struct aic_softc {TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
aic_freeze_simq(struct aic_softc *aic)
{
	xpt_freeze_simq(aic->platform_data->sim, /*count*/1);
}