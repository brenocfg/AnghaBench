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
typedef  int /*<<< orphan*/  uint32_t ;
struct pcisel {int dummy; } ;
struct pci_io {long pi_reg; int pi_width; int /*<<< orphan*/  pi_data; struct pcisel pi_sel; } ;
typedef  int /*<<< orphan*/  pi ;

/* Variables and functions */
 int /*<<< orphan*/  PCIOCREAD ; 
 int /*<<< orphan*/  bzero (struct pci_io*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_io*) ; 
 int /*<<< orphan*/  pcifd ; 

__attribute__((used)) static uint32_t
read_config(const struct pcisel *sel, long reg, int width)
{
	struct pci_io pi;

	bzero(&pi, sizeof(pi));
	pi.pi_sel = *sel;
	pi.pi_reg = reg;
	pi.pi_width = width;

	if (ioctl(pcifd, PCIOCREAD, &pi) < 0)
		return (0);				/* XXX */
	else
		return (pi.pi_data);
}