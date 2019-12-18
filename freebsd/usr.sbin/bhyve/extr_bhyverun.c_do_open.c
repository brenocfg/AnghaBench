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
struct vmctx {int dummy; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  cap_ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_MMAP_RW ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int caph_ioctls_limit (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cores ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ lpc_bootrom () ; 
 int /*<<< orphan*/  maxcpus ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sockets ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  threads ; 
 int vm_create (char const*) ; 
 int /*<<< orphan*/  vm_get_device_fd (struct vmctx*) ; 
 int /*<<< orphan*/ * vm_get_ioctls (size_t*) ; 
 struct vmctx* vm_open (char const*) ; 
 int vm_reinit (struct vmctx*) ; 
 int vm_set_topology (struct vmctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vmctx *
do_open(const char *vmname)
{
	struct vmctx *ctx;
	int error;
	bool reinit, romboot;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
	const cap_ioctl_t *cmds;	
	size_t ncmds;
#endif

	reinit = romboot = false;

	if (lpc_bootrom())
		romboot = true;

	error = vm_create(vmname);
	if (error) {
		if (errno == EEXIST) {
			if (romboot) {
				reinit = true;
			} else {
				/*
				 * The virtual machine has been setup by the
				 * userspace bootloader.
				 */
			}
		} else {
			perror("vm_create");
			exit(4);
		}
	} else {
		if (!romboot) {
			/*
			 * If the virtual machine was just created then a
			 * bootrom must be configured to boot it.
			 */
			fprintf(stderr, "virtual machine cannot be booted\n");
			exit(4);
		}
	}

	ctx = vm_open(vmname);
	if (ctx == NULL) {
		perror("vm_open");
		exit(4);
	}

#ifndef WITHOUT_CAPSICUM
	cap_rights_init(&rights, CAP_IOCTL, CAP_MMAP_RW);
	if (caph_rights_limit(vm_get_device_fd(ctx), &rights) == -1) 
		errx(EX_OSERR, "Unable to apply rights for sandbox");
	vm_get_ioctls(&ncmds);
	cmds = vm_get_ioctls(NULL);
	if (cmds == NULL)
		errx(EX_OSERR, "out of memory");
	if (caph_ioctls_limit(vm_get_device_fd(ctx), cmds, ncmds) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
	free((cap_ioctl_t *)cmds);
#endif
 
	if (reinit) {
		error = vm_reinit(ctx);
		if (error) {
			perror("vm_reinit");
			exit(4);
		}
	}
	error = vm_set_topology(ctx, sockets, cores, threads, maxcpus);
	if (error)
		errx(EX_OSERR, "vm_set_topology");
	return (ctx);
}