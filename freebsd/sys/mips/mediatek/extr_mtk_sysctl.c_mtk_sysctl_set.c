#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_SYSCTL_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MTK_SYSCTL_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mtk_sysctl_sc ; 

void
mtk_sysctl_set(uint32_t reg, uint32_t val)
{

	MTK_SYSCTL_LOCK(mtk_sysctl_sc);
	bus_write_4(mtk_sysctl_sc->mem_res, reg, val);
	MTK_SYSCTL_UNLOCK(mtk_sysctl_sc);
}