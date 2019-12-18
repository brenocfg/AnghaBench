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
struct vtcon_softc {int /*<<< orphan*/  vtcon_dev; } ;
struct virtio_console_config {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONSOLE_F_MULTIPORT ; 
 int /*<<< orphan*/  VIRTIO_CONSOLE_F_SIZE ; 
 int /*<<< orphan*/  VTCON_GET_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_console_config*) ; 
 int /*<<< orphan*/  bzero (struct virtio_console_config*,int) ; 
 int /*<<< orphan*/  cols ; 
 int /*<<< orphan*/  max_nr_ports ; 
 int /*<<< orphan*/  rows ; 

__attribute__((used)) static void
vtcon_read_config(struct vtcon_softc *sc, struct virtio_console_config *concfg)
{
	device_t dev;

	dev = sc->vtcon_dev;

	bzero(concfg, sizeof(struct virtio_console_config));

	VTCON_GET_CONFIG(dev, VIRTIO_CONSOLE_F_SIZE, cols, concfg);
	VTCON_GET_CONFIG(dev, VIRTIO_CONSOLE_F_SIZE, rows, concfg);
	VTCON_GET_CONFIG(dev, VIRTIO_CONSOLE_F_MULTIPORT, max_nr_ports, concfg);
}