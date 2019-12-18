#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; } ;
struct TYPE_12__ {int /*<<< orphan*/  pd_unit; int /*<<< orphan*/  pd_name; int /*<<< orphan*/  pc_revid; int /*<<< orphan*/  pc_progif; int /*<<< orphan*/  pc_subclass; int /*<<< orphan*/  pc_class; int /*<<< orphan*/  pc_device; int /*<<< orphan*/  pc_vendor; int /*<<< orphan*/  pc_subdevice; int /*<<< orphan*/  pc_subvendor; int /*<<< orphan*/  pc_hdr; TYPE_4__ pc_sel; } ;
struct TYPE_8__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; } ;
struct TYPE_9__ {void* pd_unit; int /*<<< orphan*/  pd_name; int /*<<< orphan*/  pc_revid; int /*<<< orphan*/  pc_progif; int /*<<< orphan*/  pc_subclass; int /*<<< orphan*/  pc_class; int /*<<< orphan*/  pc_device; int /*<<< orphan*/  pc_vendor; int /*<<< orphan*/  pc_subdevice; int /*<<< orphan*/  pc_subvendor; int /*<<< orphan*/  pc_hdr; TYPE_2__ pc_sel; } ;
struct TYPE_11__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; } ;
struct TYPE_7__ {void* pd_unit; int /*<<< orphan*/  pd_name; int /*<<< orphan*/  pc_revid; int /*<<< orphan*/  pc_progif; int /*<<< orphan*/  pc_subclass; int /*<<< orphan*/  pc_class; int /*<<< orphan*/  pc_device; int /*<<< orphan*/  pc_vendor; int /*<<< orphan*/  pc_subdevice; int /*<<< orphan*/  pc_subvendor; int /*<<< orphan*/  pc_hdr; TYPE_5__ pc_sel; } ;
struct pci_conf {int /*<<< orphan*/  pd_unit; int /*<<< orphan*/  pd_name; int /*<<< orphan*/  pc_revid; int /*<<< orphan*/  pc_progif; int /*<<< orphan*/  pc_subclass; int /*<<< orphan*/  pc_class; int /*<<< orphan*/  pc_device; int /*<<< orphan*/  pc_vendor; int /*<<< orphan*/  pc_subdevice; int /*<<< orphan*/  pc_subvendor; int /*<<< orphan*/  pc_hdr; TYPE_5__ pc_sel; } ;
union pci_conf_union {TYPE_6__ pco; TYPE_3__ pco32; TYPE_1__ pc32; struct pci_conf pc; } ;
typedef  void* uint32_t ;
typedef  int u_long ;

/* Variables and functions */
#define  PCIOCGETCONF 131 
#define  PCIOCGETCONF32 130 
#define  PCIOCGETCONF_OLD 129 
#define  PCIOCGETCONF_OLD32 128 
 int /*<<< orphan*/  memset (union pci_conf_union*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_conf_for_copyout(const struct pci_conf *pcp, union pci_conf_union *pcup,
    u_long cmd)
{

	memset(pcup, 0, sizeof(*pcup));

	switch (cmd) {
	case PCIOCGETCONF:
		pcup->pc = *pcp;
		return;

#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF32:
		pcup->pc32.pc_sel = pcp->pc_sel;
		pcup->pc32.pc_hdr = pcp->pc_hdr;
		pcup->pc32.pc_subvendor = pcp->pc_subvendor;
		pcup->pc32.pc_subdevice = pcp->pc_subdevice;
		pcup->pc32.pc_vendor = pcp->pc_vendor;
		pcup->pc32.pc_device = pcp->pc_device;
		pcup->pc32.pc_class = pcp->pc_class;
		pcup->pc32.pc_subclass = pcp->pc_subclass;
		pcup->pc32.pc_progif = pcp->pc_progif;
		pcup->pc32.pc_revid = pcp->pc_revid;
		strlcpy(pcup->pc32.pd_name, pcp->pd_name,
		    sizeof(pcup->pc32.pd_name));
		pcup->pc32.pd_unit = (uint32_t)pcp->pd_unit;
		return;
#endif

#ifdef PRE7_COMPAT
#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF_OLD32:
		pcup->pco32.pc_sel.pc_bus = pcp->pc_sel.pc_bus;
		pcup->pco32.pc_sel.pc_dev = pcp->pc_sel.pc_dev;
		pcup->pco32.pc_sel.pc_func = pcp->pc_sel.pc_func;
		pcup->pco32.pc_hdr = pcp->pc_hdr;
		pcup->pco32.pc_subvendor = pcp->pc_subvendor;
		pcup->pco32.pc_subdevice = pcp->pc_subdevice;
		pcup->pco32.pc_vendor = pcp->pc_vendor;
		pcup->pco32.pc_device = pcp->pc_device;
		pcup->pco32.pc_class = pcp->pc_class;
		pcup->pco32.pc_subclass = pcp->pc_subclass;
		pcup->pco32.pc_progif = pcp->pc_progif;
		pcup->pco32.pc_revid = pcp->pc_revid;
		strlcpy(pcup->pco32.pd_name, pcp->pd_name,
		    sizeof(pcup->pco32.pd_name));
		pcup->pco32.pd_unit = (uint32_t)pcp->pd_unit;
		return;

#endif /* COMPAT_FREEBSD32 */
	case PCIOCGETCONF_OLD:
		pcup->pco.pc_sel.pc_bus = pcp->pc_sel.pc_bus;
		pcup->pco.pc_sel.pc_dev = pcp->pc_sel.pc_dev;
		pcup->pco.pc_sel.pc_func = pcp->pc_sel.pc_func;
		pcup->pco.pc_hdr = pcp->pc_hdr;
		pcup->pco.pc_subvendor = pcp->pc_subvendor;
		pcup->pco.pc_subdevice = pcp->pc_subdevice;
		pcup->pco.pc_vendor = pcp->pc_vendor;
		pcup->pco.pc_device = pcp->pc_device;
		pcup->pco.pc_class = pcp->pc_class;
		pcup->pco.pc_subclass = pcp->pc_subclass;
		pcup->pco.pc_progif = pcp->pc_progif;
		pcup->pco.pc_revid = pcp->pc_revid;
		strlcpy(pcup->pco.pd_name, pcp->pd_name,
		    sizeof(pcup->pco.pd_name));
		pcup->pco.pd_unit = pcp->pd_unit;
		return;
#endif /* PRE7_COMPAT */

	default:
		/* programmer error */
		return;
	}
}