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
 int /*<<< orphan*/  MDIRPHY ; 
 int MII_COMMAND_ACK ; 
 int MII_COMMAND_START ; 
 int MII_COMMAND_WRITE ; 
 int /*<<< orphan*/  MWRITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_bitbang_sendbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mii_bitbang_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mii_bitbang_writereg(device_t dev, mii_bitbang_ops_t ops, int phy, int reg,
    int val)
{

	mii_bitbang_sync(dev, ops);

	mii_bitbang_sendbits(dev, ops, MII_COMMAND_START, 2);
	mii_bitbang_sendbits(dev, ops, MII_COMMAND_WRITE, 2);
	mii_bitbang_sendbits(dev, ops, phy, 5);
	mii_bitbang_sendbits(dev, ops, reg, 5);
	mii_bitbang_sendbits(dev, ops, MII_COMMAND_ACK, 2);
	mii_bitbang_sendbits(dev, ops, val, 16);

	MWRITE(MDIRPHY);
}