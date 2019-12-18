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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 char* basename (char*) ; 
 scalar_t__ linker_files_addr ; 
 scalar_t__ off_address ; 
 scalar_t__ off_filename ; 
 scalar_t__ off_next ; 
 scalar_t__ read_pointer (scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  target_read_string (scalar_t__,char**,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static int
find_kld_address (char *arg, CORE_ADDR *address)
{
	CORE_ADDR kld;
	char *kld_filename;
	char *filename;
	int error;

	if (linker_files_addr == 0 || off_address == 0 || off_filename == 0 ||
	    off_next == 0)
		return (0);

	filename = basename(arg);
	for (kld = read_pointer(linker_files_addr); kld != 0;
	     kld = read_pointer(kld + off_next)) {
		/* Try to read this linker file's filename. */
		target_read_string(read_pointer(kld + off_filename),
		    &kld_filename, PATH_MAX, &error);
		if (error)
			continue;

		/* Compare this kld's filename against our passed in name. */
		if (strcmp(kld_filename, filename) != 0) {
			xfree(kld_filename);
			continue;
		}
		xfree(kld_filename);

		/*
		 * We found a match, use its address as the base
		 * address if we can read it.
		 */
		*address = read_pointer(kld + off_address);
		if (*address == 0)
			return (0);
		return (1);
	}
	return (0);
}