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
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  uchar ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL8366_DEVNAME ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rtl8366_setPhyReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366_miiwrite(char *devname, uchar phy_adr, uchar reg, ushort data)
{
    DBG("rtl8366_miiwrite: devname=%s, addr=%#02x, reg=%#02x, data=%#04x\n",
          devname, phy_adr, reg, data);

    if (strcmp(devname, RTL8366_DEVNAME) != 0)
        return -1;

    if (rtl8366_setPhyReg(phy_adr, reg, data)) {
        printf("rtl8366_miiwrite: write failed!\n");
        return -1;
    }

    return 0;
}