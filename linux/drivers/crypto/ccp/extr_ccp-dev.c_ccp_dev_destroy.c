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
struct sp_device {struct ccp_device* ccp_data; } ;
struct ccp_device {TYPE_2__* vdata; } ;
struct TYPE_4__ {TYPE_1__* perform; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (struct ccp_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ccp_device*) ; 

void ccp_dev_destroy(struct sp_device *sp)
{
	struct ccp_device *ccp = sp->ccp_data;

	if (!ccp)
		return;

	ccp->vdata->perform->destroy(ccp);
}