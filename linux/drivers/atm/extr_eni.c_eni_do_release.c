#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eni_dev {int /*<<< orphan*/  ioaddr; } ;
struct atm_dev {TYPE_1__* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct atm_dev*) ;} ;

/* Variables and functions */
 struct eni_dev* ENI_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct atm_dev*) ; 

__attribute__((used)) static void eni_do_release(struct atm_dev *dev)
{
	struct eni_dev *ed = ENI_DEV(dev);

	dev->phy->stop(dev);
	dev->phy = NULL;
	iounmap(ed->ioaddr);
}