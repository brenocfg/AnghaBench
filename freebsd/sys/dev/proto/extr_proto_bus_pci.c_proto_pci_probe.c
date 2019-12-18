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
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCIM_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proto_pci_devnames ; 
 int /*<<< orphan*/  proto_pci_prefix ; 
 int proto_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_pci_probe(device_t dev)
{
	struct sbuf *sb;

	if ((pci_read_config(dev, PCIR_HDRTYPE, 1) & PCIM_HDRTYPE) != 0)
		return (ENXIO);

	sb = sbuf_new_auto();
	sbuf_printf(sb, "%s%d:%d:%d:%d", proto_pci_prefix, pci_get_domain(dev),
	    pci_get_bus(dev), pci_get_slot(dev), pci_get_function(dev));
	sbuf_finish(sb);
	device_set_desc_copy(dev, sbuf_data(sb));
	sbuf_delete(sb);
	return (proto_probe(dev, proto_pci_prefix, &proto_pci_devnames));
}