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
struct pci_conf_io32 {int /*<<< orphan*/  num_matches; int /*<<< orphan*/  offset; int /*<<< orphan*/  generation; int /*<<< orphan*/  status; } ;
struct pci_conf_io {int /*<<< orphan*/  num_matches; int /*<<< orphan*/  offset; int /*<<< orphan*/  generation; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  PCIOCGETCONF 131 
#define  PCIOCGETCONF32 130 
#define  PCIOCGETCONF_OLD 129 
#define  PCIOCGETCONF_OLD32 128 

__attribute__((used)) static void
pci_conf_io_update_data(const struct pci_conf_io *cio, caddr_t data,
    u_long cmd)
{
	struct pci_conf_io *d_cio;
#if defined(COMPAT_FREEBSD32)
	struct pci_conf_io32 *cio32;
#endif

	switch (cmd) {
	case PCIOCGETCONF:
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD:
#endif
		d_cio = (struct pci_conf_io *)data;
		d_cio->status = cio->status;
		d_cio->generation = cio->generation;
		d_cio->offset = cio->offset;
		d_cio->num_matches = cio->num_matches;
		return;

#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF32:
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD32:
#endif
		cio32 = (struct pci_conf_io32 *)data;

		cio32->status = cio->status;
		cio32->generation = cio->generation;
		cio32->offset = cio->offset;
		cio32->num_matches = cio->num_matches;
		return;
#endif

	default:
		/* programmer error */
		return;
	}
}