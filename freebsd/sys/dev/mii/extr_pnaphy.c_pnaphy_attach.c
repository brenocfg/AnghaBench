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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MIIF_IS_HPNA ; 
 int MIIF_NOISOLATE ; 
 int MIIF_NOMANPAUSE ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pnaphy_funcs ; 

__attribute__((used)) static int
pnaphy_attach(device_t dev)
{

	mii_phy_dev_attach(dev, MIIF_NOISOLATE | MIIF_IS_HPNA |
	   MIIF_NOMANPAUSE, &pnaphy_funcs, 1);
	return (0);
}