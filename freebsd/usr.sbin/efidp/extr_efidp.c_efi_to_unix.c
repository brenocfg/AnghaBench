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
typedef  scalar_t__ efidp ;
typedef  int /*<<< orphan*/  dpbuf ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int MAXSIZE ; 
 size_t efidp_parse_device_path (char*,scalar_t__,int) ; 
 int efivar_device_path_to_unix_path (scalar_t__,char**,char**,char**) ; 
 int errno ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 char* trim (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
efi_to_unix(void)
{
	char buffer[MAXSIZE];
	char dpbuf[MAXSIZE];
	efidp dp;
	size_t dplen;
	char *walker, *dev, *relpath, *abspath;
	int rv;

	dp = (efidp)dpbuf;
	while (fgets(buffer, sizeof(buffer), stdin)) {
		walker= trim(buffer);
		dplen = efidp_parse_device_path(walker, dp, sizeof(dpbuf));
		rv = efivar_device_path_to_unix_path(dp, &dev, &relpath, &abspath);
		if (rv == 0)
			printf("%s:%s %s\n", dev, relpath, abspath);
		else {
			errno = rv;
			warn("Can't convert '%s' to unix", walker);
		}
	}
}