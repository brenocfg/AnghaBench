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
 int SATA_ORB1_OFF ; 
 int SATA_ORB2_OFF ; 
 int SATA_ORB3_OFF ; 
 int SATA_ORB4_OFF ; 
 int /*<<< orphan*/ ** sata_regs_base ; 
 int /*<<< orphan*/ * wr_sata_orb1 ; 
 int /*<<< orphan*/ * wr_sata_orb2 ; 
 int /*<<< orphan*/ * wr_sata_orb3 ; 
 int /*<<< orphan*/ * wr_sata_orb4 ; 

__attribute__((used)) static void xfer_wr_shadow_to_orbs(int device)
{
	*(sata_regs_base[device] + SATA_ORB1_OFF) = wr_sata_orb1[device];
	*(sata_regs_base[device] + SATA_ORB2_OFF) = wr_sata_orb2[device];
	*(sata_regs_base[device] + SATA_ORB3_OFF) = wr_sata_orb3[device];
	*(sata_regs_base[device] + SATA_ORB4_OFF) = wr_sata_orb4[device];
}