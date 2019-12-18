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
typedef  int u_long ;
struct pci_conf_old32 {int dummy; } ;
struct pci_conf_old {int dummy; } ;
struct pci_conf32 {int dummy; } ;
struct pci_conf {int dummy; } ;

/* Variables and functions */
#define  PCIOCGETCONF 131 
#define  PCIOCGETCONF32 130 
#define  PCIOCGETCONF_OLD 129 
#define  PCIOCGETCONF_OLD32 128 

__attribute__((used)) static size_t
pci_conf_size(u_long cmd)
{

	switch (cmd) {
	case PCIOCGETCONF:
		return (sizeof(struct pci_conf));
#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF32:
		return (sizeof(struct pci_conf32));
#endif
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD:
		return (sizeof(struct pci_conf_old));
#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF_OLD32:
		return (sizeof(struct pci_conf_old32));
#endif
#endif
	default:
		/* programmer error */
		return (0);
	}
}