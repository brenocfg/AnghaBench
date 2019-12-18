#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  datasize; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  command_buffer; } ;
typedef  TYPE_1__ ips_ioctl_t ;
typedef  int /*<<< orphan*/  ips_generic_cmd ;
struct TYPE_6__ {int /*<<< orphan*/  callback; int /*<<< orphan*/  command_buffer; TYPE_1__* arg; } ;
typedef  TYPE_2__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_ioctl_callback ; 
 int /*<<< orphan*/  ips_ioctl_finish ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ips_ioctl_start(ips_command_t *command)
{
	ips_ioctl_t *ioctl_cmd = command->arg;
	memcpy(command->command_buffer, ioctl_cmd->command_buffer,
		sizeof(ips_generic_cmd));
	command->callback = ips_ioctl_finish;
	bus_dmamap_load(ioctl_cmd->dmatag, ioctl_cmd->dmamap, 
			ioctl_cmd->data_buffer,ioctl_cmd->datasize, 
			ips_ioctl_callback, command, 0);
	return 0;
}