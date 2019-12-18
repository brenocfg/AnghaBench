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
struct pci_io {int pi_width; void* pi_data; void* pi_reg; int /*<<< orphan*/  pi_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIOCWRITE ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  getsel (char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pci_io*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
writeit(const char *name, const char *reg, const char *data, int width)
{
	int fd;
	struct pci_io pi;

	pi.pi_sel = getsel(name);
	pi.pi_reg = strtoul(reg, (char **)0, 0); /* XXX error check */
	pi.pi_width = width;
	pi.pi_data = strtoul(data, (char **)0, 0); /* XXX error check */

	fd = open(_PATH_DEVPCI, O_RDWR, 0);
	if (fd < 0)
		err(1, "%s", _PATH_DEVPCI);

	if (ioctl(fd, PCIOCWRITE, &pi) < 0)
		err(1, "ioctl(PCIOCWRITE)");
	close(fd);
}