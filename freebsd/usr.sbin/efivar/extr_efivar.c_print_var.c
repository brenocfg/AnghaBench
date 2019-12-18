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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 scalar_t__ Aflag ; 
 int /*<<< orphan*/  Nflag ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  asciidump (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ bflag ; 
 int /*<<< orphan*/  bindump (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  devpath_dump (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ dflag ; 
 int efi_get_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_print_load_option (int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fromfile ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ load_opt_flag ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int open (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pflag ; 
 int /*<<< orphan*/  pretty_guid (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t read (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  utf8dump (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
print_var(efi_guid_t *guid, char *name)
{
	uint32_t att;
	uint8_t *data;
	size_t datalen;
	char *gname = NULL;
	int rv;

	if (guid)
		pretty_guid(guid, &gname);
	if (pflag || fromfile) {
		if (fromfile) {
			int fd;

			fd = open(fromfile, O_RDONLY);
			if (fd < 0)
				err(1, "open %s", fromfile);
			data = malloc(64 * 1024);
			if (data == NULL)
				err(1, "malloc");
			datalen = read(fd, data, 64 * 1024);
			if (datalen <= 0)
				err(1, "read");
			close(fd);
		} else {
			rv = efi_get_variable(*guid, name, &data, &datalen, &att);
			if (rv < 0)
				err(1, "fetching %s-%s", gname, name);
		}


		if (!Nflag)
			printf("%s-%s\n", gname, name);
		if (load_opt_flag)
			efi_print_load_option(data, datalen, Aflag, bflag, uflag);
		else if (Aflag)
			asciidump(data, datalen);
		else if (uflag)
			utf8dump(data, datalen);
		else if (bflag)
			bindump(data, datalen);
		else if (dflag)
			devpath_dump(data, datalen);
		else
			hexdump(data, datalen);
	} else {
		printf("%s-%s", gname, name);
	}
	free(gname);
	if (!Nflag)
		printf("\n");
}