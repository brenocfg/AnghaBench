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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct preloaded_file {int /*<<< orphan*/  f_size; } ;
struct multiboot_header {scalar_t__ magic; int flags; scalar_t__ checksum; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int EFTYPE ; 
 int ENOMEM ; 
 scalar_t__ MULTIBOOT_HEADER_MAGIC ; 
 int /*<<< orphan*/  MULTIBOOT_SEARCH ; 
 int MULTIBOOT_SUPPORTED_FLAGS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int elf32_loadfile_raw (char*,int /*<<< orphan*/ ,struct preloaded_file**,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int read (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
multiboot_loadfile(char *filename, uint64_t dest,
    struct preloaded_file **result)
{
	uint32_t		*magic;
	int			 i, error;
	caddr_t			 header_search;
	ssize_t			 search_size;
	int			 fd;
	struct multiboot_header	*header;
	char			*cmdline;

	/*
	 * Read MULTIBOOT_SEARCH size in order to search for the
	 * multiboot magic header.
	 */
	if (filename == NULL)
		return (EFTYPE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (errno);
	header_search = malloc(MULTIBOOT_SEARCH);
	if (header_search == NULL) {
		close(fd);
		return (ENOMEM);
	}
	search_size = read(fd, header_search, MULTIBOOT_SEARCH);
	magic = (uint32_t *)header_search;

	header = NULL;
	for (i = 0; i < (search_size / sizeof(uint32_t)); i++) {
		if (magic[i] == MULTIBOOT_HEADER_MAGIC) {
			header = (struct multiboot_header *)&magic[i];
			break;
		}
	}

	if (header == NULL) {
		error = EFTYPE;
		goto out;
	}

	/* Valid multiboot header has been found, validate checksum */
	if (header->magic + header->flags + header->checksum != 0) {
		printf(
	"Multiboot checksum failed, magic: 0x%x flags: 0x%x checksum: 0x%x\n",
	header->magic, header->flags, header->checksum);
		error = EFTYPE;
		goto out;
	}

	if ((header->flags & ~MULTIBOOT_SUPPORTED_FLAGS) != 0) {
		printf("Unsupported multiboot flags found: 0x%x\n",
		    header->flags);
		error = EFTYPE;
		goto out;
	}

	error = elf32_loadfile_raw(filename, dest, result, 1);
	if (error != 0) {
		printf(
	"elf32_loadfile_raw failed: %d unable to load multiboot kernel\n",
	error);
		goto out;
	}

	/*
	 * f_addr is already aligned to PAGE_SIZE, make sure
	 * f_size it's also aligned so when the modules are loaded
	 * they are aligned to PAGE_SIZE.
	 */
	(*result)->f_size = roundup((*result)->f_size, PAGE_SIZE);

out:
	free(header_search);
	close(fd);
	return (error);
}