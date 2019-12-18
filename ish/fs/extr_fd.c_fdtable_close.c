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
struct fdtable {int /*<<< orphan*/  cloexec; int /*<<< orphan*/ ** files; } ;
struct fd {int /*<<< orphan*/ * inode; } ;
typedef  size_t fd_t ;

/* Variables and functions */
 int _EBADF ; 
 int /*<<< orphan*/  bit_clear (size_t,int /*<<< orphan*/ ) ; 
 int fd_close (struct fd*) ; 
 struct fd* fdtable_get (struct fdtable*,size_t) ; 
 int /*<<< orphan*/  file_lock_remove_owned_by (struct fd*,struct fdtable*) ; 

__attribute__((used)) static int fdtable_close(struct fdtable *table, fd_t f) {
    struct fd *fd = fdtable_get(table, f);
    if (fd == NULL)
        return _EBADF;
    if (fd->inode != NULL) // temporary hack for files like sockets that right now don't have inodes but will eventually
        file_lock_remove_owned_by(fd, table);
    int err = fd_close(fd);
    table->files[f] = NULL;
    bit_clear(f, table->cloexec);
    return err;
}