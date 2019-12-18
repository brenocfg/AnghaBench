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
typedef  int UINTN ;
struct TYPE_2__ {int /*<<< orphan*/  DeviceHandle; } ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_1__* boot_img ; 
 int /*<<< orphan*/  efi_freebsd_delenv (char const*) ; 
 scalar_t__ efi_freebsd_getenv (char const*,char*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  parse_loader_efi_config (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
read_loader_env(const char *name, char *def_fn, bool once)
{
	UINTN len;
	char *fn, *freeme = NULL;

	len = 0;
	fn = def_fn;
	if (efi_freebsd_getenv(name, NULL, &len) == EFI_BUFFER_TOO_SMALL) {
		freeme = fn = malloc(len + 1);
		if (fn != NULL) {
			if (efi_freebsd_getenv(name, fn, &len) != EFI_SUCCESS) {
				free(fn);
				fn = NULL;
				printf(
			    "Can't fetch FreeBSD::%s we know is there\n", name);
			} else {
				/*
				 * if tagged as 'once' delete the env variable so we
				 * only use it once.
				 */
				if (once)
					efi_freebsd_delenv(name);
				/*
				 * We malloced 1 more than len above, then redid the call.
				 * so now we have room at the end of the string to NUL terminate
				 * it here, even if the typical idium would have '- 1' here to
				 * not overflow. len should be the same on return both times.
				 */
				fn[len] = '\0';
			}
		} else {
			printf(
		    "Can't allocate %d bytes to fetch FreeBSD::%s env var\n",
			    len, name);
		}
	}
	if (fn) {
		printf("    Reading loader env vars from %s\n", fn);
		parse_loader_efi_config(boot_img->DeviceHandle, fn);
	}
}