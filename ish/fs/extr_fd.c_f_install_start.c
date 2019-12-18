#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fdtable {unsigned int size; int /*<<< orphan*/  cloexec; struct fd** files; } ;
struct fd {int dummy; } ;
typedef  scalar_t__ fd_t ;
struct TYPE_2__ {struct fdtable* files; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE_ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bit_clear (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fd_close (struct fd*) ; 
 int fdtable_expand (struct fdtable*,scalar_t__) ; 
 unsigned int rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fd_t f_install_start(struct fd *fd, fd_t start) {
    assert(start >= 0);
    struct fdtable *table = current->files;
    unsigned size = rlimit(RLIMIT_NOFILE_);
    if (size > table->size)
        size = table->size;

    fd_t f;
    for (f = start; (unsigned) f < size; f++)
        if (table->files[f] == NULL)
            break;
    if ((unsigned) f >= size) {
        int err = fdtable_expand(table, f);
        if (err < 0)
            f = err;
    }

    if (f >= 0) {
        table->files[f] = fd;
        bit_clear(f, table->cloexec);
    } else {
        fd_close(fd);
    }
    return f;
}