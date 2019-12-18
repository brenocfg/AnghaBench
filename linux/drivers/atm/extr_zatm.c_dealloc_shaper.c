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
struct zatm_dev {int ubr; int free_shapers; int /*<<< orphan*/  lock; scalar_t__ ubr_ref_cnt; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 struct zatm_dev* ZATM_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uPD98401_PS (int) ; 
 int uPD98401_PS_E ; 
 int zpeekl (struct zatm_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpokel (struct zatm_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dealloc_shaper(struct atm_dev *dev,int shaper)
{
	struct zatm_dev *zatm_dev;
	unsigned long flags;

	zatm_dev = ZATM_DEV(dev);
	if (shaper == zatm_dev->ubr) {
		if (--zatm_dev->ubr_ref_cnt) return;
		zatm_dev->ubr = -1;
	}
	spin_lock_irqsave(&zatm_dev->lock, flags);
	zpokel(zatm_dev,zpeekl(zatm_dev,uPD98401_PS(shaper)) & ~uPD98401_PS_E,
	    uPD98401_PS(shaper));
	spin_unlock_irqrestore(&zatm_dev->lock, flags);
	zatm_dev->free_shapers |= 1 << shaper;
}