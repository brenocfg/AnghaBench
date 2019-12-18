#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_3__*) ;int /*<<< orphan*/  command_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_10__ {int /*<<< orphan*/  reserve2; int /*<<< orphan*/  id; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ ips_generic_cmd ;
struct TYPE_11__ {int /*<<< orphan*/  command_dmamap; int /*<<< orphan*/  id; scalar_t__ command_buffer; int /*<<< orphan*/  callback; TYPE_1__* sc; } ;
typedef  TYPE_3__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 scalar_t__ COMMAND_ERROR (TYPE_3__*) ; 
 int /*<<< orphan*/  IPS_CSL ; 
 int /*<<< orphan*/  IPS_ERROR_TABLE_CMD ; 
 int /*<<< orphan*/  PRINTF (int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_insert_free_cmd (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ips_wakeup_callback ; 
 int /*<<< orphan*/  sema_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int ips_send_error_table_cmd(ips_command_t *command)
{
	ips_softc_t *sc = command->sc;
	ips_generic_cmd *command_struct;

	PRINTF(10,"ips test: got a command, building errortable command\n");
	command->callback = ips_wakeup_callback;
	command_struct = (ips_generic_cmd *)command->command_buffer;
	command_struct->command = IPS_ERROR_TABLE_CMD;
	command_struct->id = command->id;
	command_struct->reserve2 = IPS_CSL;
	bus_dmamap_sync(sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_PREWRITE);
	sc->ips_issue_cmd(command);
	if (COMMAND_ERROR(command) == 0)
		sema_wait(&sc->cmd_sema);
	ips_insert_free_cmd(sc, command);
	return 0;
}