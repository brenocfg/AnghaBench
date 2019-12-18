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
struct TYPE_2__ {int /*<<< orphan*/ * cdev; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 

void destroy_char_dev(struct pqisrc_softstate *softs)
{
	DBG_FUNC("IN\n");
	if (softs->os_specific.cdev) {
		destroy_dev(softs->os_specific.cdev);
		softs->os_specific.cdev = NULL;
	}
	DBG_FUNC("OUT\n");
}