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
struct bio {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  ips_command_t ;

/* Variables and functions */
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ ips_get_free_cmd (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_send_io_request (int /*<<< orphan*/ *,struct bio*) ; 

void ips_start_io_request(ips_softc_t *sc)
{
	struct bio *iobuf;
	ips_command_t *command;

	iobuf = bioq_first(&sc->queue);
	if(!iobuf)
		return;

	if (ips_get_free_cmd(sc, &command, 0))
		return;
	
	bioq_remove(&sc->queue, iobuf);
	ips_send_io_request(command, iobuf);
	return;
}