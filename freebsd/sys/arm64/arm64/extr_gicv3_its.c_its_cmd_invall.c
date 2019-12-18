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
struct its_col {int dummy; } ;
struct TYPE_2__ {struct its_col* col; } ;
struct its_cmd_desc {TYPE_1__ cmd_desc_invall; int /*<<< orphan*/  cmd_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITS_CMD_INVALL ; 
 int /*<<< orphan*/  its_cmd_send (int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void
its_cmd_invall(device_t dev, struct its_col *col)
{
	struct its_cmd_desc desc;

	desc.cmd_type = ITS_CMD_INVALL;
	desc.cmd_desc_invall.col = col;

	its_cmd_send(dev, &desc);
}