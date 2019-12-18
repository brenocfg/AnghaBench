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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct ksyms_softc {int /*<<< orphan*/  sc_obj; int /*<<< orphan*/  sc_objsz; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PROT_READ ; 
 int devfs_get_cdevpriv (void**) ; 
 scalar_t__ round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ksyms_mmap_single(struct cdev *dev, vm_ooffset_t *offset, vm_size_t size,
    vm_object_t *objp, int nprot)
{
	struct ksyms_softc *sc;
	vm_object_t obj;
	int error;

	error = devfs_get_cdevpriv((void **)&sc);
	if (error != 0)
		return (error);

	if (*offset < 0 || *offset >= round_page(sc->sc_objsz) ||
	    size > round_page(sc->sc_objsz) - *offset ||
	    (nprot & ~PROT_READ) != 0)
		return (EINVAL);

	obj = sc->sc_obj;
	vm_object_reference(obj);
	*objp = obj;
	return (0);
}