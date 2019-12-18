#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* cdev; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;
struct TYPE_4__ {struct pqisrc_softstate* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,int) ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  UID_ROOT ; 
 TYPE_2__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  smartpqi_cdevsw ; 

int create_char_dev(struct pqisrc_softstate *softs, int card_index)
{
	int error = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN idx = %d\n", card_index);

	softs->os_specific.cdev = make_dev(&smartpqi_cdevsw, card_index,
				UID_ROOT, GID_OPERATOR, 0640,
				"smartpqi%u", card_index);
	if(softs->os_specific.cdev) {
		softs->os_specific.cdev->si_drv1 = softs;
	} else {
		error = PQI_STATUS_FAILURE;
	}

	DBG_FUNC("OUT error = %d\n", error);
	return error;
}