#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
struct TYPE_6__ {char* VendorID; char* ProductID; } ;
struct TYPE_5__ {char* ProductID; } ;
typedef  TYPE_1__ MPI2_IOC_FACTS_REPLY ;
typedef  TYPE_2__ MPI2_FW_IMAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 char* MPI2_MFGPAGE_VENDORID_LSI ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 unsigned char* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mps_firmware_send (int,unsigned char*,int,int) ; 
 TYPE_1__* mps_get_iocfacts (int) ; 
 int mps_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_unit ; 
 int /*<<< orphan*/  munmap (unsigned char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
flash_update(int argc, char **argv)
{
	int error, fd;
	unsigned char *mem = NULL;
	struct stat st;
	bool bios = false;
	MPI2_FW_IMAGE_HEADER *fwheader;
	MPI2_IOC_FACTS_REPLY *facts;

	if (argc < 2) {
		warnx("missing argument: expecting 'firmware' or bios'");
		return (EINVAL);
	}

	if (strcmp(argv[1], "bios") == 0) {
		bios = true;
	} else if (strcmp(argv[1], "firmware") != 0) {
		warnx("Invalid argument '%s', expecting 'firmware' or 'bios'",
		    argv[1]);
	}

	if (argc > 4) {
		warnx("update firmware: extra arguments");
		return (EINVAL);
	}

	if (argc != 3) {
		warnx("no firmware specified");
		return (EINVAL);
	}

	if (stat(argv[2], &st) == -1) {
		error = errno;
		warn("stat");
		return (error);
	}

	fd = open(argv[2], O_RDONLY);
	if (fd < 0) {
		error = errno;
		warn("open");
		return (error);
	}

	mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mem == MAP_FAILED) {
		error = errno;
		warn("mmap");
		close(fd);
		return (error);
	}
	close(fd);

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		munmap(mem, st.st_size);
		return (error);
	}

	if ((facts = mps_get_iocfacts(fd)) == NULL) {
		warnx("could not get controller IOCFacts\n");
		munmap(mem, st.st_size);
		close(fd);
		return (EINVAL);
	}

	if (bios) {
		/* Check boot record magic number */
		if (((mem[0x01]<<8) + mem[0x00]) != 0xaa55) {
			warnx("Invalid bios: no boot record magic number");
			munmap(mem, st.st_size);
			close(fd);
			free(facts);
			return (1);
		}
		if ((st.st_size % 512) != 0) {
			warnx("Invalid bios: size not a multiple of 512");
			munmap(mem, st.st_size);
			close(fd);
			free(facts);
			return (1);
		}
	} else {
		fwheader = (MPI2_FW_IMAGE_HEADER *)mem;
		if (fwheader->VendorID != MPI2_MFGPAGE_VENDORID_LSI) {
			warnx("Invalid firmware:");
			warnx("  Expected Vendor ID: %04x",
			    MPI2_MFGPAGE_VENDORID_LSI);
			warnx("  Image Vendor ID: %04x", fwheader->VendorID);
			munmap(mem, st.st_size);
			close(fd);
			free(facts);
			return (1);
		}

		if (fwheader->ProductID != facts->ProductID) {
			warnx("Invalid image:");
			warnx("  Expected Product ID: %04x", facts->ProductID);
			warnx("  Image Product ID: %04x", fwheader->ProductID);
			munmap(mem, st.st_size);
			close(fd);
			free(facts);
			return (1);
		}
	}

	printf("Updating %s...\n", argv[1]);
	if (mps_firmware_send(fd, mem, st.st_size, bios) < 0) {
		warnx("Fail to update %s", argv[1]);
		munmap(mem, st.st_size);
		close(fd);
		free(facts);
		return (1);
	}

	munmap(mem, st.st_size);
	close(fd);
	free(facts);
	printf("%s successfully updated\n", argv[1]);
	return (0);
}