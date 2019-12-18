#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  used_commands; int /*<<< orphan*/  free_cmd_list; int /*<<< orphan*/ * staticcmd; int /*<<< orphan*/  cmd_sema; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_STATIC_BUSY ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ sema_value (int /*<<< orphan*/ *) ; 

void ips_insert_free_cmd(ips_softc_t *sc, ips_command_t *command)
{

	if (sema_value(&sc->cmd_sema) != 0)
		panic("ips: command returned non-zero semaphore");

	if (command != sc->staticcmd) {
		SLIST_INSERT_HEAD(&sc->free_cmd_list, command, next);
		(sc->used_commands)--;
	} else {
		sc->state &= ~IPS_STATIC_BUSY;
	}
}