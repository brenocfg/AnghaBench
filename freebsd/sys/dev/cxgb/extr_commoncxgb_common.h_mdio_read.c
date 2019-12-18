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
struct cphy {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int*) ;int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int*) ; 

__attribute__((used)) static inline int mdio_read(struct cphy *phy, int mmd, int reg,
			    unsigned int *valp)
{
	return phy->mdio_read(phy->adapter, phy->addr, mmd, reg, valp);
}