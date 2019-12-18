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
struct TYPE_5__ {int value; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; TYPE_1__ status; } ;
typedef  TYPE_2__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ COMMAND_ERROR (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void 
ipsd_dump_block_complete(ips_command_t *command)
{

	if (COMMAND_ERROR(command))
		printf("ipsd_dump completion error= 0x%x\n",
		    command->status.value);

	bus_dmamap_sync(command->data_dmatag, command->data_dmamap,
	    BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(command->data_dmatag, command->data_dmamap);
}