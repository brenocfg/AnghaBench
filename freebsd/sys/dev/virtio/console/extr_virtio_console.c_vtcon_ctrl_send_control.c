#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct vtcon_softc {int vtcon_flags; } ;
struct virtio_console_control {void* value; void* event; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int VTCON_FLAG_MULTIPORT ; 
 int /*<<< orphan*/  vtcon_ctrl_poll (struct vtcon_softc*,struct virtio_console_control*) ; 

__attribute__((used)) static void
vtcon_ctrl_send_control(struct vtcon_softc *sc, uint32_t portid,
    uint16_t event, uint16_t value)
{
	struct virtio_console_control control;

	if ((sc->vtcon_flags & VTCON_FLAG_MULTIPORT) == 0)
		return;

	control.id = portid;
	control.event = event;
	control.value = value;

	vtcon_ctrl_poll(sc, &control);
}