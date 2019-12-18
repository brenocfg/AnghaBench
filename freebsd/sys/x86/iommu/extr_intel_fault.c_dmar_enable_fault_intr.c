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
struct dmar_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_FECTL_IM ; 
 int /*<<< orphan*/  DMAR_FECTL_REG ; 
 int /*<<< orphan*/  dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmar_enable_fault_intr(struct dmar_unit *unit)
{
	uint32_t fectl;

	DMAR_ASSERT_LOCKED(unit);
	fectl = dmar_read4(unit, DMAR_FECTL_REG);
	fectl &= ~DMAR_FECTL_IM;
	dmar_write4(unit, DMAR_FECTL_REG, fectl);
}