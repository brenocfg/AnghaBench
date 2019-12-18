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
typedef  int /*<<< orphan*/  uint8_t ;
struct ctl_scsiio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ctl_set_overlapped_tag(struct ctl_scsiio *ctsio, uint8_t tag)
{
	/* TAGGED OVERLAPPED COMMANDS (NN = QUEUE TAG) */
	ctl_set_sense(ctsio,
		      /*current_error*/ 1,
		      /*sense_key*/ SSD_KEY_ILLEGAL_REQUEST,
		      /*asc*/ 0x4D,
		      /*ascq*/ tag,
		      SSD_ELEM_NONE);
}