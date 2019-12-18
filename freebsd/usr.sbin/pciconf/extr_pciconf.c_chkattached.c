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
struct pci_io {scalar_t__ pi_data; int /*<<< orphan*/  pi_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIOCATTACHED ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int exitstatus ; 
 int /*<<< orphan*/  getsel (char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pci_io*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,char*) ; 

__attribute__((used)) static void
chkattached(const char *name)
{
	int fd;
	struct pci_io pi;

	pi.pi_sel = getsel(name);

	fd = open(_PATH_DEVPCI, O_RDWR, 0);
	if (fd < 0)
		err(1, "%s", _PATH_DEVPCI);

	if (ioctl(fd, PCIOCATTACHED, &pi) < 0)
		err(1, "ioctl(PCIOCATTACHED)");

	exitstatus = pi.pi_data ? 0 : 2; /* exit(2), if NOT attached */
	printf("%s: %s%s\n", name, pi.pi_data == 0 ? "not " : "", "attached");
	close(fd);
}