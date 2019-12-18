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
struct fdtable {int refcount; int /*<<< orphan*/  lock; int /*<<< orphan*/ * cloexec; int /*<<< orphan*/ * files; scalar_t__ size; } ;

/* Variables and functions */
 struct fdtable* ERR_PTR (int) ; 
 int _ENOMEM ; 
 int fdtable_resize (struct fdtable*,int) ; 
 int /*<<< orphan*/  free (struct fdtable*) ; 
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 
 struct fdtable* malloc (int) ; 

struct fdtable *fdtable_new(int size) {
    struct fdtable *fdt = malloc(sizeof(struct fdtable));
    if (fdt == NULL)
        return ERR_PTR(_ENOMEM);
    fdt->refcount = 1;
    fdt->size = 0;
    fdt->files = NULL;
    fdt->cloexec = NULL;
    lock_init(&fdt->lock);
    int err = fdtable_resize(fdt, size);
    if (err < 0) {
        free(fdt);
        return ERR_PTR(err);
    }
    return fdt;
}