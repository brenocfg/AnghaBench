#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tag_action; } ;
union ccb {TYPE_1__ csio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {union ccb* cm_ccb; } ;
typedef  TYPE_2__ rcb_t ;

/* Variables and functions */
#define  MSG_HEAD_OF_Q_TAG 130 
#define  MSG_ORDERED_Q_TAG 129 
#define  MSG_SIMPLE_Q_TAG 128 
 int /*<<< orphan*/  SOP_TASK_ATTRIBUTE_HEAD_OF_QUEUE ; 
 int /*<<< orphan*/  SOP_TASK_ATTRIBUTE_ORDERED ; 
 int /*<<< orphan*/  SOP_TASK_ATTRIBUTE_SIMPLE ; 

uint8_t os_get_task_attr(rcb_t *rcb) 
{
	union ccb *ccb = rcb->cm_ccb;
	uint8_t tag_action = SOP_TASK_ATTRIBUTE_SIMPLE;

	switch(ccb->csio.tag_action) {
	case MSG_HEAD_OF_Q_TAG:
		tag_action = SOP_TASK_ATTRIBUTE_HEAD_OF_QUEUE;
		break;
	case MSG_ORDERED_Q_TAG:
		tag_action = SOP_TASK_ATTRIBUTE_ORDERED;
		break;
	case MSG_SIMPLE_Q_TAG:
	default:
		tag_action = SOP_TASK_ATTRIBUTE_SIMPLE;
		break;
	}
	return tag_action;
}