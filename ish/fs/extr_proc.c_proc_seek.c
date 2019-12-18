#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct fd {int offset; TYPE_2__ proc; } ;
typedef  int off_t_ ;

/* Variables and functions */
 int LSEEK_CUR ; 
 int LSEEK_END ; 
 int LSEEK_SET ; 
 int _EINVAL ; 
 int proc_refresh_data (struct fd*) ; 

__attribute__((used)) static off_t_ proc_seek(struct fd *fd, off_t_ off, int whence) {
    int err = proc_refresh_data(fd);
    if (err < 0)
        return err;

    off_t_ old_off = fd->offset;
    if (whence == LSEEK_SET)
        fd->offset = off;
    else if (whence == LSEEK_CUR)
        fd->offset += off;
    else if (whence == LSEEK_END)
        fd->offset = fd->proc.data.size + off;
    else
        return _EINVAL;

    if (fd->offset < 0) {
        fd->offset = old_off;
        return _EINVAL;
    }
    return fd->offset;
}