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
 int /*<<< orphan*/  AQ_THERMAL1 ; 
 int /*<<< orphan*/  AQ_THERMAL2 ; 
 int /*<<< orphan*/  MDIO_DEV_VEND1 ; 
 scalar_t__ mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int
aq100x_temperature(struct cphy *phy)
{
	unsigned int v;

	if (mdio_read(phy, MDIO_DEV_VEND1, AQ_THERMAL2, &v) ||
	    v == 0xffff || (v & 1) != 1)
		return (0xffff);

	if (mdio_read(phy, MDIO_DEV_VEND1, AQ_THERMAL1, &v))
		return (0xffff);

	return ((int)((signed char)(v >> 8)));
}