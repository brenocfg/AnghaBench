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
struct mpt_softc {TYPE_1__* ioc_page2; } ;
struct TYPE_2__ {scalar_t__ MaxPhysDisks; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int
mpt_raid_probe(struct mpt_softc *mpt)
{

	if (mpt->ioc_page2 == NULL || mpt->ioc_page2->MaxPhysDisks == 0) {
		return (ENODEV);
	}
	return (0);
}