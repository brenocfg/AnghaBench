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
typedef  int /*<<< orphan*/  mii_bitbang_ops_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDC ; 
 int MDI ; 
 int MDIRHOST ; 
 int MDIRPHY ; 
 int MII_COMMAND_READ ; 
 int MII_COMMAND_START ; 
 int MREAD ; 
 int /*<<< orphan*/  MWRITE (int) ; 
 int /*<<< orphan*/  mii_bitbang_sendbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mii_bitbang_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mii_bitbang_readreg(device_t dev, mii_bitbang_ops_t ops, int phy, int reg)
{
	int i, error, val;

	mii_bitbang_sync(dev, ops);

	mii_bitbang_sendbits(dev, ops, MII_COMMAND_START, 2);
	mii_bitbang_sendbits(dev, ops, MII_COMMAND_READ, 2);
	mii_bitbang_sendbits(dev, ops, phy, 5);
	mii_bitbang_sendbits(dev, ops, reg, 5);

	/* Switch direction to PHY->host, without a clock transition. */
	MWRITE(MDIRHOST);

	/* Turnaround clock. */
	MWRITE(MDIRHOST | MDC);
	MWRITE(MDIRHOST);

	/* Check for error. */
	error = MREAD & MDI;

	/* Idle clock. */
	MWRITE(MDIRHOST | MDC);
	MWRITE(MDIRHOST);

	val = 0;
	for (i = 0; i < 16; i++) {
		val <<= 1;
		/* Read data prior to clock low-high transition. */
		if (error == 0 && (MREAD & MDI) != 0)
			val |= 1;

		MWRITE(MDIRHOST | MDC);
		MWRITE(MDIRHOST);
	}

	/* Set direction to host->PHY, without a clock transition. */
	MWRITE(MDIRPHY);

	return (error != 0 ? 0 : val);
}