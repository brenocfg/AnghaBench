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
typedef  int uint16_t ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  SBcode; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* emu_cards ; 
 unsigned int emu_getcard (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_pci_probe(device_t dev)
{
	struct sbuf *s;
	unsigned int thiscard = 0;
	uint16_t vendor;

	vendor = pci_read_config(dev, PCIR_DEVVENDOR, /* bytes */ 2);
	if (vendor != 0x1102)
		return (ENXIO);	/* Not Creative */

	thiscard = emu_getcard(dev);
	if (thiscard == 0)
		return (ENXIO);

	s = sbuf_new(NULL, NULL, 4096, 0);
	if (s == NULL)
		return (ENOMEM);
	sbuf_printf(s, "Creative %s [%s]", emu_cards[thiscard].desc, emu_cards[thiscard].SBcode);
	sbuf_finish(s);

	device_set_desc_copy(dev, sbuf_data(s));

	sbuf_delete(s);

	return (BUS_PROBE_DEFAULT);
}