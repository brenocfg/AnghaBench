#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int ExtPageLength; int ExtPageType; int PageType; } ;
struct TYPE_3__ {int PageLength; int PageType; } ;
typedef  TYPE_1__ MPI2_CONFIG_PAGE_HEADER ;
typedef  TYPE_2__ MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 int HD_REVERSED ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 char* get_page_name (int) ; 
 int /*<<< orphan*/  hexdump (void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mps_ioc_status (int /*<<< orphan*/ ) ; 
 int mps_open (int /*<<< orphan*/ ) ; 
 void* mps_read_config_page (int,int,int,scalar_t__,int /*<<< orphan*/ *) ; 
 void* mps_read_extended_config_page (int,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_unit ; 
 int /*<<< orphan*/  printf (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
show_cfgpage(int ac, char **av)
{
	MPI2_CONFIG_PAGE_HEADER *hdr;
	MPI2_CONFIG_EXTENDED_PAGE_HEADER *ehdr;
	void *data;
	uint32_t addr;
	uint16_t IOCStatus;
	uint8_t page, num;
	int fd, error, len, attrs;
	char *pgname, *pgattr;

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		return (error);
	}

	addr = 0;
	num = 0;
	page = 0;

	switch (ac) {
	case 4:
		addr = (uint32_t)strtoul(av[3], NULL, 0);
	case 3:
		num = (uint8_t)strtoul(av[2], NULL, 0);
	case 2:
		page = (uint8_t)strtoul(av[1], NULL, 0);
		break;
	default:
		errno = EINVAL;
		warn("cfgpage: not enough arguments");
		return (EINVAL);
	}

	if (page >= 0x10)
		data = mps_read_extended_config_page(fd, page, 0, num, addr,
		    &IOCStatus);
	 else 
		data = mps_read_config_page(fd, page, num, addr, &IOCStatus);

	if (data == NULL) {
		error = errno;
		warn("Error retrieving cfg page: %s\n",
		    mps_ioc_status(IOCStatus));
		return (error);
	}

	if (page >= 0x10) {
		ehdr = data;
		len = ehdr->ExtPageLength * 4;
		page = ehdr->ExtPageType;
		attrs = ehdr->PageType >> 4;
	} else {
		hdr = data;
		len = hdr->PageLength * 4;
		page = hdr->PageType & 0xf;
		attrs = hdr->PageType >> 4;
	}

	pgname = get_page_name(page);
	if (attrs == 0)
		pgattr = "Read-only";
	else if (attrs == 1)
		pgattr = "Read-Write";
	else if (attrs == 2)
		pgattr = "Read-Write Persistent";
	else
		pgattr = "Unknown Page Attribute";

	printf("Page 0x%x: %s %d, %s\n", page, pgname, num, pgattr);
	hexdump(data, len, NULL, HD_REVERSED | 4);
	free(data);
	close(fd);
	return (0);
}