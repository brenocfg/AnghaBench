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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  ips_command_t ;

/* Variables and functions */
 scalar_t__ COMMAND_ERROR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPS_STATIC_FLAG ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ips_get_free_cmd (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_send_flush_cache_cmd (int /*<<< orphan*/ *) ; 

int ips_flush_cache(ips_softc_t *sc)
{
	ips_command_t *command;

	device_printf(sc->dev, "flushing cache\n");
	if (ips_get_free_cmd(sc, &command, IPS_STATIC_FLAG)){
		device_printf(sc->dev, "ERROR: unable to get a command! can't flush cache!\n");
	}
	ips_send_flush_cache_cmd(command);
	if(COMMAND_ERROR(command)){
		device_printf(sc->dev, "ERROR: cache flush command failed!\n");
	}
	return 0;
}