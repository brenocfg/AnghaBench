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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
vm_device_open(const char *name)
{
	int fd, len;
	char *vmfile;

	len = strlen("/dev/vmm/") + strlen(name) + 1;
	vmfile = malloc(len);
	assert(vmfile != NULL);
	snprintf(vmfile, len, "/dev/vmm/%s", name);

	/* Open the device file */
	fd = open(vmfile, O_RDWR, 0);

	free(vmfile);
	return (fd);
}