#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bhndb_pci_probe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fini; int /*<<< orphan*/  read; int /*<<< orphan*/  tell; int /*<<< orphan*/  map; } ;
struct bhndb_pci_eio {int mapped; struct bhndb_pci_probe* probe; scalar_t__ size; scalar_t__ addr; TYPE_1__ eio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhndb_pci_eio_map ; 
 int /*<<< orphan*/  bhndb_pci_eio_read ; 
 int /*<<< orphan*/  bhndb_pci_eio_tell ; 
 int /*<<< orphan*/  memset (struct bhndb_pci_eio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bhndb_pci_eio_init(struct bhndb_pci_eio *pio, struct bhndb_pci_probe *probe)
{
	memset(pio, 0, sizeof(*pio));

	pio->eio.map = bhndb_pci_eio_map;
	pio->eio.tell = bhndb_pci_eio_tell;
	pio->eio.read = bhndb_pci_eio_read;
	pio->eio.fini = NULL;

	pio->mapped = false;
	pio->addr = 0;
	pio->size = 0;
	pio->probe = probe;
}