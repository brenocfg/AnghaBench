#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_mgrp_t ;
struct TYPE_4__ {int /*<<< orphan*/  mgrp_list; } ;
typedef  TYPE_1__ osm_mgrp_box_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cl_item_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cl_qlist_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_item ; 
 int /*<<< orphan*/  mgrp_box_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  mgrp_delete (int /*<<< orphan*/ *) ; 

void osm_mgrp_box_delete(osm_mgrp_box_t *mbox)
{
	osm_mgrp_t *mgrp;

	while (cl_qlist_count(&mbox->mgrp_list)) {
		mgrp = cl_item_obj(cl_qlist_remove_head(&mbox->mgrp_list),
				   mgrp, list_item);
		mgrp_delete(mgrp);
	}
	mgrp_box_delete(mbox);
}