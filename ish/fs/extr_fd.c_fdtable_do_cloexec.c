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
struct fdtable {unsigned int size; int /*<<< orphan*/  lock; int /*<<< orphan*/  cloexec; } ;
typedef  scalar_t__ fd_t ;

/* Variables and functions */
 scalar_t__ bit_test (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtable_close (struct fdtable*,scalar_t__) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void fdtable_do_cloexec(struct fdtable *table) {
    lock(&table->lock);
    for (fd_t f = 0; (unsigned) f < table->size; f++)
        if (bit_test(f, table->cloexec))
            fdtable_close(table, f);
    unlock(&table->lock);
}