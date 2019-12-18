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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int dummy; } ;
struct pci_devinst {struct hda_softc* pi_arg; } ;
struct hda_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hda_read (struct hda_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
pci_hda_read(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
    int baridx, uint64_t offset, int size)
{
	struct hda_softc *sc = pi->pi_arg;
	uint64_t value = 0;

	assert(sc);
	assert(baridx == 0);
	assert(size <= 4);

	value = hda_read(sc, offset);

	DPRINTF("offset: 0x%lx value: 0x%lx\n", offset, value);

	return (value);
}