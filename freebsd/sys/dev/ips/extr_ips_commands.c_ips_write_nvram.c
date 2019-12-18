#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* ips_issue_cmd ) (TYPE_4__*) ;int /*<<< orphan*/  command_dmatag; int /*<<< orphan*/  adapter_type; } ;
typedef  TYPE_1__ ips_softc_t ;
struct TYPE_8__ {int pagenum; int rw; int /*<<< orphan*/  id; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ ips_rw_nvram_cmd ;
struct TYPE_9__ {int /*<<< orphan*/  operating_system; int /*<<< orphan*/  driver_low; int /*<<< orphan*/  driver_high; int /*<<< orphan*/  adapter_type; } ;
typedef  TYPE_3__ ips_nvram_page5 ;
struct TYPE_10__ {int /*<<< orphan*/  command_dmamap; TYPE_3__* data_buffer; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; int /*<<< orphan*/  id; scalar_t__ command_buffer; int /*<<< orphan*/  callback; TYPE_1__* sc; } ;
typedef  TYPE_4__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  IPS_OS_FREEBSD ; 
 int /*<<< orphan*/  IPS_RW_NVRAM_CMD ; 
 int /*<<< orphan*/  IPS_VERSION_MAJOR ; 
 int /*<<< orphan*/  IPS_VERSION_MINOR ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_wakeup_callback ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void ips_write_nvram(ips_command_t *command){
	ips_softc_t *sc = command->sc;
	ips_rw_nvram_cmd *command_struct;
	ips_nvram_page5 *nvram;

	/*FIXME check for error */
	command->callback = ips_wakeup_callback;
	command_struct = (ips_rw_nvram_cmd *)command->command_buffer;
	command_struct->command = IPS_RW_NVRAM_CMD;
	command_struct->id = command->id;
	command_struct->pagenum = 5;
	command_struct->rw	= 1; /*write*/
	bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
				BUS_DMASYNC_POSTREAD);
	nvram = command->data_buffer;
	/* retrieve adapter info and save in sc */
	sc->adapter_type = nvram->adapter_type;

	strncpy(nvram->driver_high, IPS_VERSION_MAJOR, 4);
	strncpy(nvram->driver_low, IPS_VERSION_MINOR, 4);
	nvram->operating_system = IPS_OS_FREEBSD;	
	bus_dmamap_sync(sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_PREWRITE);
	sc->ips_issue_cmd(command);
}