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
struct fdtable {scalar_t__ refcount; unsigned int size; int /*<<< orphan*/  lock; struct fdtable* cloexec; struct fdtable* files; } ;
typedef  scalar_t__ fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdtable_close (struct fdtable*,scalar_t__) ; 
 int /*<<< orphan*/  free (struct fdtable*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void fdtable_release(struct fdtable *table) {
    lock(&table->lock);
    if (--table->refcount == 0) {
        for (fd_t f = 0; (unsigned) f < table->size; f++)
            fdtable_close(table, f);
        free(table->files);
        free(table->cloexec);
        unlock(&table->lock);
        free(table);
    } else {
        unlock(&table->lock);
    }
}