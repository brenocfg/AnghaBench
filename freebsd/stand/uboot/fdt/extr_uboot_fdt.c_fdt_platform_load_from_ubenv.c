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
struct fdt_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ fdt_load_dtb_addr (struct fdt_header*) ; 
 int /*<<< orphan*/  printf (char*,struct fdt_header*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 char* ub_env_get (char const*) ; 

__attribute__((used)) static int
fdt_platform_load_from_ubenv(const char *var)
{
	struct fdt_header *hdr;
	const char *s;
	char *p;

	s = ub_env_get(var);
	if (s == NULL || *s == '\0')
		return (1);

	hdr = (struct fdt_header *)strtoul(s, &p, 16);
	if (*p != '\0')
		return (1);

	if (fdt_load_dtb_addr(hdr) == 0) {
		printf("Using DTB provided by U-Boot at "
		    "address %p.\n", hdr);
		return (0);
	}

	return (1);
}