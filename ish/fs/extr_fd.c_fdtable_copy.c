#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fdtable {int size; int /*<<< orphan*/  lock; TYPE_1__** cloexec; TYPE_1__** files; } ;
struct fd {int dummy; } ;
typedef  int fd_t ;
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int BITS_SIZE (int) ; 
 scalar_t__ IS_ERR (struct fdtable*) ; 
 struct fdtable* fdtable_new (int) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

struct fdtable *fdtable_copy(struct fdtable *table) {
    lock(&table->lock);
    int size = table->size;
    struct fdtable *new_table = fdtable_new(size);
    if (IS_ERR(new_table)) {
        unlock(&table->lock);
        return new_table;
    }
    memcpy(new_table->files, table->files, sizeof(struct fd *) * size);
    for (fd_t f = 0; f < size; f++)
        if (new_table->files[f])
            new_table->files[f]->refcount++;
    memcpy(new_table->cloexec, table->cloexec, BITS_SIZE(size));
    unlock(&table->lock);
    return new_table;
}