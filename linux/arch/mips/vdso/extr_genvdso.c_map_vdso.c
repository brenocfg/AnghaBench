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
struct stat {size_t st_size; } ;
struct TYPE_2__ {int* e_ident; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_machine; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
#define  ELFCLASS32 131 
#define  ELFCLASS64 130 
#define  ELFDATA2LSB 129 
#define  ELFDATA2MSB 128 
 int /*<<< orphan*/  ELFMAG ; 
 scalar_t__ EM_MIPS ; 
 scalar_t__ ET_DYN ; 
 int HOST_ORDER ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SELFMAG ; 
 int elf_class ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int need_swap ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_uint16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *map_vdso(const char *path, size_t *_size)
{
	int fd;
	struct stat stat;
	void *addr;
	const Elf32_Ehdr *ehdr;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "%s: Failed to open '%s': %s\n", program_name,
			path, strerror(errno));
		return NULL;
	}

	if (fstat(fd, &stat) != 0) {
		fprintf(stderr, "%s: Failed to stat '%s': %s\n", program_name,
			path, strerror(errno));
		return NULL;
	}

	addr = mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
		    0);
	if (addr == MAP_FAILED) {
		fprintf(stderr, "%s: Failed to map '%s': %s\n", program_name,
			path, strerror(errno));
		return NULL;
	}

	/* ELF32/64 header formats are the same for the bits we're checking. */
	ehdr = addr;

	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
		fprintf(stderr, "%s: '%s' is not an ELF file\n", program_name,
			path);
		return NULL;
	}

	elf_class = ehdr->e_ident[EI_CLASS];
	switch (elf_class) {
	case ELFCLASS32:
	case ELFCLASS64:
		break;
	default:
		fprintf(stderr, "%s: '%s' has invalid ELF class\n",
			program_name, path);
		return NULL;
	}

	switch (ehdr->e_ident[EI_DATA]) {
	case ELFDATA2LSB:
	case ELFDATA2MSB:
		need_swap = ehdr->e_ident[EI_DATA] != HOST_ORDER;
		break;
	default:
		fprintf(stderr, "%s: '%s' has invalid ELF data order\n",
			program_name, path);
		return NULL;
	}

	if (swap_uint16(ehdr->e_machine) != EM_MIPS) {
		fprintf(stderr,
			"%s: '%s' has invalid ELF machine (expected EM_MIPS)\n",
			program_name, path);
		return NULL;
	} else if (swap_uint16(ehdr->e_type) != ET_DYN) {
		fprintf(stderr,
			"%s: '%s' has invalid ELF type (expected ET_DYN)\n",
			program_name, path);
		return NULL;
	}

	*_size = stat.st_size;
	return addr;
}