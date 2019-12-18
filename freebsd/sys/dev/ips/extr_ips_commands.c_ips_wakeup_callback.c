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
struct TYPE_5__ {TYPE_1__* sc; int /*<<< orphan*/  command_dmamap; } ;
typedef  TYPE_2__ ips_command_t ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  command_dmatag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ips_wakeup_callback(ips_command_t *command)
{
	bus_dmamap_sync(command->sc->command_dmatag, command->command_dmamap, 
			BUS_DMASYNC_POSTWRITE);
	sema_post(&command->sc->cmd_sema);
}