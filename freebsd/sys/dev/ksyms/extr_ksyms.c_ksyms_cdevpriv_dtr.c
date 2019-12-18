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
typedef  int /*<<< orphan*/ * vm_object_t ;
struct ksyms_softc {int /*<<< orphan*/ * sc_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct ksyms_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_KSYMS ; 
 int /*<<< orphan*/  free (struct ksyms_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksyms_mtx ; 
 int /*<<< orphan*/  sc_list ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ksyms_cdevpriv_dtr(void *data)
{
	struct ksyms_softc *sc;
	vm_object_t obj;

	sc = (struct ksyms_softc *)data;

	sx_xlock(&ksyms_mtx);
	LIST_REMOVE(sc, sc_list);
	sx_xunlock(&ksyms_mtx);
	obj = sc->sc_obj;
	if (obj != NULL)
		vm_object_deallocate(obj);
	free(sc, M_KSYMS);
}