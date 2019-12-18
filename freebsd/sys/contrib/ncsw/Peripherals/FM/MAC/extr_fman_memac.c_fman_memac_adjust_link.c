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
struct memac_regs {int /*<<< orphan*/  if_mode; } ;
typedef  enum enet_speed { ____Placeholder_enet_speed } enet_speed ;
typedef  enum enet_interface { ____Placeholder_enet_interface } enet_interface ;

/* Variables and functions */
 int E_ENET_IF_RGMII ; 
#define  E_ENET_SPEED_10 130 
#define  E_ENET_SPEED_100 129 
#define  E_ENET_SPEED_1000 128 
 int /*<<< orphan*/  IF_MODE_HD ; 
 int /*<<< orphan*/  IF_MODE_RGMII_10 ; 
 int /*<<< orphan*/  IF_MODE_RGMII_100 ; 
 int /*<<< orphan*/  IF_MODE_RGMII_1000 ; 
 int /*<<< orphan*/  IF_MODE_RGMII_AUTO ; 
 int /*<<< orphan*/  IF_MODE_RGMII_FD ; 
 int /*<<< orphan*/  IF_MODE_RGMII_SP_MASK ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_memac_adjust_link(struct memac_regs *regs,
        enum enet_interface iface_mode,
        enum enet_speed speed, bool full_dx)
{
    uint32_t    tmp;

    tmp = ioread32be(&regs->if_mode);

    if (full_dx)
        tmp &= ~IF_MODE_HD;
    else
        tmp |= IF_MODE_HD;

    if (iface_mode == E_ENET_IF_RGMII) {
        /* Configure RGMII in manual mode */
        tmp &= ~IF_MODE_RGMII_AUTO;
        tmp &= ~IF_MODE_RGMII_SP_MASK;

        if (full_dx)
            tmp |= IF_MODE_RGMII_FD;
        else
            tmp &= ~IF_MODE_RGMII_FD;

        switch (speed) {
        case E_ENET_SPEED_1000:
            tmp |= IF_MODE_RGMII_1000;
            break;
        case E_ENET_SPEED_100:
            tmp |= IF_MODE_RGMII_100;
            break;
        case E_ENET_SPEED_10:
            tmp |= IF_MODE_RGMII_10;
            break;
        default:
            break;
        }
    }

    iowrite32be(tmp, &regs->if_mode);
}