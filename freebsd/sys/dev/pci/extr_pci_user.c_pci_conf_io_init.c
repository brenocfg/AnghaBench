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
struct pci_conf_io32 {int /*<<< orphan*/  status; int /*<<< orphan*/  generation; int /*<<< orphan*/  offset; int /*<<< orphan*/  matches; int /*<<< orphan*/  num_matches; int /*<<< orphan*/  match_buf_len; int /*<<< orphan*/  patterns; int /*<<< orphan*/  num_patterns; int /*<<< orphan*/  pat_buf_len; } ;
struct pci_conf_io {int /*<<< orphan*/  status; int /*<<< orphan*/  generation; int /*<<< orphan*/  offset; void* matches; int /*<<< orphan*/  num_matches; int /*<<< orphan*/  match_buf_len; void* patterns; int /*<<< orphan*/  num_patterns; int /*<<< orphan*/  pat_buf_len; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  PCIOCGETCONF 131 
#define  PCIOCGETCONF32 130 
#define  PCIOCGETCONF_OLD 129 
#define  PCIOCGETCONF_OLD32 128 

__attribute__((used)) static void
pci_conf_io_init(struct pci_conf_io *cio, caddr_t data, u_long cmd)
{
#if defined(COMPAT_FREEBSD32)
	struct pci_conf_io32 *cio32;
#endif

	switch (cmd) {
	case PCIOCGETCONF:
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD:
#endif
		*cio = *(struct pci_conf_io *)data;
		return;

#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF32:
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD32:
#endif
               cio32 = (struct pci_conf_io32 *)data;
               cio->pat_buf_len = cio32->pat_buf_len;
               cio->num_patterns = cio32->num_patterns;
               cio->patterns = (void *)(uintptr_t)cio32->patterns;
               cio->match_buf_len = cio32->match_buf_len;
               cio->num_matches = cio32->num_matches;
               cio->matches = (void *)(uintptr_t)cio32->matches;
               cio->offset = cio32->offset;
               cio->generation = cio32->generation;
               cio->status = cio32->status;
               return;
#endif

	default:
		/* programmer error */
		return;
	}
}