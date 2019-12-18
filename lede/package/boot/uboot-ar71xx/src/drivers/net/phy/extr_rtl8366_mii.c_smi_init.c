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

/* Variables and functions */
 int /*<<< orphan*/  MII_SCKINPUT ; 
 int /*<<< orphan*/  MII_SDAINPUT ; 
 int /*<<< orphan*/  MII_SETSCK (int) ; 
 int /*<<< orphan*/  MII_SETSDA (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void smi_init(void)
{
    MII_SDAINPUT;
    MII_SCKINPUT;

	MII_SETSDA(1);
	MII_SETSCK(1);

    udelay(20);
}