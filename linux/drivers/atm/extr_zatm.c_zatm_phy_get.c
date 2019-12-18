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
struct zatm_dev {int dummy; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CER ; 
 int /*<<< orphan*/  CMR ; 
 struct zatm_dev* ZATM_DEV (struct atm_dev*) ; 
 unsigned long uPD98401_IA_B0 ; 
 unsigned long uPD98401_IA_RW ; 
 unsigned long uPD98401_IA_TGT_PHY ; 
 unsigned long uPD98401_IA_TGT_SHIFT ; 
 unsigned long uPD98401_IND_ACC ; 
 int zin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zout (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwait () ; 

__attribute__((used)) static unsigned char zatm_phy_get(struct atm_dev *dev,unsigned long addr)
{
	struct zatm_dev *zatm_dev;

	zatm_dev = ZATM_DEV(dev);
	zwait();
	zout(uPD98401_IND_ACC | uPD98401_IA_B0 | uPD98401_IA_RW |
	  (uPD98401_IA_TGT_PHY << uPD98401_IA_TGT_SHIFT) | addr,CMR);
	zwait();
	return zin(CER) & 0xff;
}