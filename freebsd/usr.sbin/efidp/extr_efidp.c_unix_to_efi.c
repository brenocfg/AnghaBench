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
typedef  int /*<<< orphan*/ * efidp ;
typedef  int /*<<< orphan*/  efi ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int MAXSIZE ; 
 scalar_t__ efidp_format_device_path (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efidp_size (int /*<<< orphan*/ *) ; 
 int efivar_unix_path_to_device_path (char*,int /*<<< orphan*/ **) ; 
 int errno ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 char* trim (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
unix_to_efi(void)
{
	char buffer[MAXSIZE];
	char efi[MAXSIZE];
	efidp dp;
	char *walker;
	int rv;

	dp = NULL;
	while (fgets(buffer, sizeof(buffer), stdin)) {
		walker= trim(buffer);
		free(dp);
		dp = NULL;
		rv = efivar_unix_path_to_device_path(walker, &dp);
		if (rv != 0 || dp == NULL) {
			errno = rv;
			warn("Can't convert '%s' to efi", walker);
			continue;
		}
		if (efidp_format_device_path(efi, sizeof(efi),
		    dp, efidp_size(dp)) < 0) {
			warnx("Can't format dp for '%s'", walker);
			continue;
		}
		printf("%s\n", efi);
	}
	free(dp);
}