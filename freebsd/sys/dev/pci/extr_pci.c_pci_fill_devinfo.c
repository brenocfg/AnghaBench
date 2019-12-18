#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_7__ {int pc_domain; int pc_bus; int pc_dev; int pc_func; } ;
struct TYPE_8__ {int pc_hdr; int pc_class; int pc_subclass; int pc_progif; int pc_revid; void* pc_device; void* pc_vendor; int /*<<< orphan*/  pc_subdevice; int /*<<< orphan*/  pc_subvendor; TYPE_1__ pc_sel; } ;
struct TYPE_9__ {int domain; int bus; int slot; int func; int cmdreg; int statreg; int baseclass; int subclass; int progif; int revid; int hdrtype; int cachelnsz; int lattimer; int intpin; int intline; int mfdev; void* device; void* vendor; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; int /*<<< orphan*/ * iov; int /*<<< orphan*/  maps; } ;
struct pci_devinfo {TYPE_2__ conf; TYPE_3__ cfg; } ;
typedef  TYPE_3__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_MFDEV ; 
 int PCIM_STATUS_CAPPRESENT ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int /*<<< orphan*/  PCIR_INTPIN ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_PROGIF ; 
 int /*<<< orphan*/  PCIR_REVID ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 struct pci_devinfo* PCI_ALLOC_DEVINFO (int /*<<< orphan*/ ) ; 
 int REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pci_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_devq ; 
 int /*<<< orphan*/  pci_fixancient (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_generation ; 
 int /*<<< orphan*/  pci_hdrtypedata (int /*<<< orphan*/ ,int,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  pci_links ; 
 int /*<<< orphan*/  pci_numdevs ; 
 int /*<<< orphan*/  pci_read_cap (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static struct pci_devinfo *
pci_fill_devinfo(device_t pcib, device_t bus, int d, int b, int s, int f,
    uint16_t vid, uint16_t did)
{
	struct pci_devinfo *devlist_entry;
	pcicfgregs *cfg;

	devlist_entry = PCI_ALLOC_DEVINFO(bus);

	cfg = &devlist_entry->cfg;

	cfg->domain		= d;
	cfg->bus		= b;
	cfg->slot		= s;
	cfg->func		= f;
	cfg->vendor		= vid;
	cfg->device		= did;
	cfg->cmdreg		= REG(PCIR_COMMAND, 2);
	cfg->statreg		= REG(PCIR_STATUS, 2);
	cfg->baseclass		= REG(PCIR_CLASS, 1);
	cfg->subclass		= REG(PCIR_SUBCLASS, 1);
	cfg->progif		= REG(PCIR_PROGIF, 1);
	cfg->revid		= REG(PCIR_REVID, 1);
	cfg->hdrtype		= REG(PCIR_HDRTYPE, 1);
	cfg->cachelnsz		= REG(PCIR_CACHELNSZ, 1);
	cfg->lattimer		= REG(PCIR_LATTIMER, 1);
	cfg->intpin		= REG(PCIR_INTPIN, 1);
	cfg->intline		= REG(PCIR_INTLINE, 1);

	cfg->mfdev		= (cfg->hdrtype & PCIM_MFDEV) != 0;
	cfg->hdrtype		&= ~PCIM_MFDEV;
	STAILQ_INIT(&cfg->maps);

	cfg->iov		= NULL;

	pci_fixancient(cfg);
	pci_hdrtypedata(pcib, b, s, f, cfg);

	if (REG(PCIR_STATUS, 2) & PCIM_STATUS_CAPPRESENT)
		pci_read_cap(pcib, cfg);

	STAILQ_INSERT_TAIL(&pci_devq, devlist_entry, pci_links);

	devlist_entry->conf.pc_sel.pc_domain = cfg->domain;
	devlist_entry->conf.pc_sel.pc_bus = cfg->bus;
	devlist_entry->conf.pc_sel.pc_dev = cfg->slot;
	devlist_entry->conf.pc_sel.pc_func = cfg->func;
	devlist_entry->conf.pc_hdr = cfg->hdrtype;

	devlist_entry->conf.pc_subvendor = cfg->subvendor;
	devlist_entry->conf.pc_subdevice = cfg->subdevice;
	devlist_entry->conf.pc_vendor = cfg->vendor;
	devlist_entry->conf.pc_device = cfg->device;

	devlist_entry->conf.pc_class = cfg->baseclass;
	devlist_entry->conf.pc_subclass = cfg->subclass;
	devlist_entry->conf.pc_progif = cfg->progif;
	devlist_entry->conf.pc_revid = cfg->revid;

	pci_numdevs++;
	pci_generation++;

	return (devlist_entry);
}