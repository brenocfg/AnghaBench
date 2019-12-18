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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline bool
isQEMU(void) {
#ifdef __FreeBSD__
	char *vm_guest_name_buf;
	size_t len;
	bool is_vm;

	if (sysctlbyname("kern.vm_guest", NULL, &len, NULL, 0) == -1)
		err(EXIT_FAILURE, "sysctl");

	if ((vm_guest_name_buf = malloc(len)) == NULL)
		err(EXIT_FAILURE, "malloc");

	if (sysctlbyname("kern.vm_guest", vm_guest_name_buf, &len, NULL, 0)
	    == -1)
		err(EXIT_FAILURE, "sysctl");

	if (strcmp(vm_guest_name_buf, "none") == 0)
		is_vm = false;
	else
		is_vm = true;

	free(vm_guest_name_buf);

	return is_vm;
#else
#if defined(__i386__) || defined(__x86_64__)
	char name[1024];
	size_t len = sizeof(name);

	if (sysctlbyname("machdep.cpu_brand", name, &len, NULL, 0) == -1) {
		if (errno == ENOENT)
			return false;
		err(EXIT_FAILURE, "sysctl");
	}
	return strstr(name, "QEMU") != NULL;
#else
	return false;
#endif
#endif
}