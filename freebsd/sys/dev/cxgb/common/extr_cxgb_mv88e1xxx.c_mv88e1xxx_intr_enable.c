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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_ENABLE_MASK ; 
 int /*<<< orphan*/  MV88E1XXX_INTR_ENABLE ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e1xxx_intr_enable(struct cphy *cphy)
{
	return mdio_write(cphy, 0, MV88E1XXX_INTR_ENABLE, INTR_ENABLE_MASK);
}