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
struct sp_device {TYPE_1__* dev_vdata; } ;
struct TYPE_2__ {scalar_t__ psp_vdata; scalar_t__ ccp_vdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_dev_init (struct sp_device*) ; 
 int /*<<< orphan*/  psp_dev_init (struct sp_device*) ; 
 int /*<<< orphan*/  sp_add_device (struct sp_device*) ; 

int sp_init(struct sp_device *sp)
{
	sp_add_device(sp);

	if (sp->dev_vdata->ccp_vdata)
		ccp_dev_init(sp);

	if (sp->dev_vdata->psp_vdata)
		psp_dev_init(sp);
	return 0;
}