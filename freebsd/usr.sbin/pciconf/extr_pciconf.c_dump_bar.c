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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int pc_domain; int pc_bus; int pc_dev; int pc_func; } ;
struct pci_bar_mmap {int pbm_reg; int pbm_bar_length; int pbm_bar_off; int /*<<< orphan*/  pbm_map_length; scalar_t__ pbm_map_base; TYPE_1__ pbm_sel; int /*<<< orphan*/  pbm_memattr; scalar_t__ pbm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIOCBARMMAP ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,scalar_t__,int,int,int,int,int) ; 
 size_t fwrite (int*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ getsel (char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pci_bar_mmap*) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 void* strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_bar(const char *name, const char *reg, const char *bar_start,
    const char *bar_count, int width, int verbose)
{
	struct pci_bar_mmap pbm;
	uint32_t *dd;
	uint16_t *dh;
	uint8_t *db;
	uint64_t *dx, a, start, count;
	char *el;
	size_t res;
	int fd;

	start = 0;
	if (bar_start != NULL) {
		start = strtoul(bar_start, &el, 0);
		if (*el != '\0')
			errx(1, "Invalid bar start specification %s",
			    bar_start);
	}
	count = 0;
	if (bar_count != NULL) {
		count = strtoul(bar_count, &el, 0);
		if (*el != '\0')
			errx(1, "Invalid count specification %s",
			    bar_count);
	}

	pbm.pbm_sel = getsel(name);
	pbm.pbm_reg = strtoul(reg, &el, 0);
	if (*reg == '\0' || *el != '\0')
		errx(1, "Invalid bar specification %s", reg);
	pbm.pbm_flags = 0;
	pbm.pbm_memattr = VM_MEMATTR_UNCACHEABLE; /* XXX */

	fd = open(_PATH_DEVPCI, O_RDWR, 0);
	if (fd < 0)
		err(1, "%s", _PATH_DEVPCI);

	if (ioctl(fd, PCIOCBARMMAP, &pbm) < 0)
		err(1, "ioctl(PCIOCBARMMAP)");

	if (count == 0)
		count = pbm.pbm_bar_length / width;
	if (start + count < start || (start + count) * width < (uint64_t)width)
		errx(1, "(start + count) x width overflow");
	if ((start + count) * width > pbm.pbm_bar_length) {
		if (start * width > pbm.pbm_bar_length)
			count = 0;
		else
			count = (pbm.pbm_bar_length - start * width) / width;
	}
	if (verbose) {
		fprintf(stderr,
		    "Dumping pci%d:%d:%d:%d BAR %x mapped base %p "
		    "off %#x length %#jx from %#jx count %#jx in %d-bytes\n",
		    pbm.pbm_sel.pc_domain, pbm.pbm_sel.pc_bus,
		    pbm.pbm_sel.pc_dev, pbm.pbm_sel.pc_func,
		    pbm.pbm_reg, pbm.pbm_map_base, pbm.pbm_bar_off,
		    pbm.pbm_bar_length, start, count, width);
	}
	switch (width) {
	case 1:
		db = (uint8_t *)(uintptr_t)((uintptr_t)pbm.pbm_map_base +
		    pbm.pbm_bar_off + start * width);
		for (a = 0; a < count; a += width, db++) {
			res = fwrite(db, width, 1, stdout);
			if (res != 1) {
				errx(1, "error writing to stdout");
				break;
			}
		}
		break;
	case 2:
		dh = (uint16_t *)(uintptr_t)((uintptr_t)pbm.pbm_map_base +
		    pbm.pbm_bar_off + start * width);
		for (a = 0; a < count; a += width, dh++) {
			res = fwrite(dh, width, 1, stdout);
			if (res != 1) {
				errx(1, "error writing to stdout");
				break;
			}
		}
		break;
	case 4:
		dd = (uint32_t *)(uintptr_t)((uintptr_t)pbm.pbm_map_base +
		    pbm.pbm_bar_off + start * width);
		for (a = 0; a < count; a += width, dd++) {
			res = fwrite(dd, width, 1, stdout);
			if (res != 1) {
				errx(1, "error writing to stdout");
				break;
			}
		}
		break;
	case 8:
		dx = (uint64_t *)(uintptr_t)((uintptr_t)pbm.pbm_map_base +
		    pbm.pbm_bar_off + start * width);
		for (a = 0; a < count; a += width, dx++) {
			res = fwrite(dx, width, 1, stdout);
			if (res != 1) {
				errx(1, "error writing to stdout");
				break;
			}
		}
		break;
	default:
		errx(1, "invalid access width");
	}

	munmap((void *)pbm.pbm_map_base, pbm.pbm_map_length);
	close(fd);
}