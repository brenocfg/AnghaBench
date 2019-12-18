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
struct vmmdev_softc {int /*<<< orphan*/  vm; } ;
struct vm_memseg {int /*<<< orphan*/  segid; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VMMDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ VM_MEMSEG_NAME (struct vm_memseg*) ; 
 int copystr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int devmem_create_cdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vm_alloc_memseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_free_memseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alloc_memseg(struct vmmdev_softc *sc, struct vm_memseg *mseg)
{
	char *name;
	int error;
	bool sysmem;

	error = 0;
	name = NULL;
	sysmem = true;

	/*
	 * The allocation is lengthened by 1 to hold a terminating NUL.  It'll
	 * by stripped off when devfs processes the full string.
	 */
	if (VM_MEMSEG_NAME(mseg)) {
		sysmem = false;
		name = malloc(sizeof(mseg->name), M_VMMDEV, M_WAITOK);
		error = copystr(mseg->name, name, sizeof(mseg->name), NULL);
		if (error)
			goto done;
	}

	error = vm_alloc_memseg(sc->vm, mseg->segid, mseg->len, sysmem);
	if (error)
		goto done;

	if (VM_MEMSEG_NAME(mseg)) {
		error = devmem_create_cdev(vm_name(sc->vm), mseg->segid, name);
		if (error)
			vm_free_memseg(sc->vm, mseg->segid);
		else
			name = NULL;	/* freed when 'cdev' is destroyed */
	}
done:
	free(name, M_VMMDEV);
	return (error);
}