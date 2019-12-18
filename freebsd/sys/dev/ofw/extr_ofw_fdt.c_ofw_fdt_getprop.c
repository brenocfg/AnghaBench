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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ofw_t ;
typedef  int /*<<< orphan*/  cpuid ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_boot_cpuid_phys (scalar_t__) ; 
 char* fdt_get_name (scalar_t__,int,int*) ; 
 void* fdt_getprop (scalar_t__,int,char const*,int*) ; 
 int fdt_num_mem_rsv (scalar_t__) ; 
 int fdt_off_mem_rsvmap (scalar_t__) ; 
 int fdt_path_offset (scalar_t__,char*) ; 
 int fdt_phandle_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ fdtp ; 
 int /*<<< orphan*/  min (int,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (void*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
ofw_fdt_getprop(ofw_t ofw, phandle_t package, const char *propname, void *buf,
    size_t buflen)
{
	const void *prop;
	const char *name;
	int len, offset;
	uint32_t cpuid;

	offset = fdt_phandle_offset(package);
	if (offset < 0)
		return (-1);

	prop = fdt_getprop(fdtp, offset, propname, &len);

	if (prop == NULL && strcmp(propname, "name") == 0) {
		/* Emulate the 'name' property */
		name = fdt_get_name(fdtp, offset, &len);
		strncpy(buf, name, buflen);
		return (len + 1);
	}

	if (prop == NULL && offset == fdt_path_offset(fdtp, "/chosen")) {
		if (strcmp(propname, "fdtbootcpu") == 0) {
			cpuid = cpu_to_fdt32(fdt_boot_cpuid_phys(fdtp));
			len = sizeof(cpuid);
			prop = &cpuid;
		}
		if (strcmp(propname, "fdtmemreserv") == 0) {
			prop = (char *)fdtp + fdt_off_mem_rsvmap(fdtp);
			len = sizeof(uint64_t)*2*fdt_num_mem_rsv(fdtp);
		}
	}

	if (prop == NULL)
		return (-1);

	bcopy(prop, buf, min(len, buflen));

	return (len);
}