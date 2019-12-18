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
typedef  int u16 ;
struct TYPE_2__ {int* extendedComID; } ;
struct opal_header {TYPE_1__ cp; } ;
struct opal_dev {scalar_t__ cmd; } ;

/* Variables and functions */

__attribute__((used)) static void set_comid(struct opal_dev *cmd, u16 comid)
{
	struct opal_header *hdr = (struct opal_header *)cmd->cmd;

	hdr->cp.extendedComID[0] = comid >> 8;
	hdr->cp.extendedComID[1] = comid;
	hdr->cp.extendedComID[2] = 0;
	hdr->cp.extendedComID[3] = 0;
}