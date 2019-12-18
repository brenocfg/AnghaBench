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
typedef  int u_int ;
struct open_file {scalar_t__ f_fsdata; } ;
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int offset; scalar_t__ c; TYPE_1__ de; } ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int cv4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static off_t
dos_seek(struct open_file *fd, off_t offset, int whence)
{
    off_t off;
    u_int size;
    DOS_FILE *f = (DOS_FILE *)fd->f_fsdata;

    size = cv4(f->de.size);
    switch (whence) {
    case SEEK_SET:
        off = 0;
        break;
    case SEEK_CUR:
        off = f->offset;
        break;
    case SEEK_END:
        off = size;
        break;
    default:
	errno = EINVAL;
	return (-1);
    }
    off += offset;
    if (off < 0 || off > size) {
	errno = EINVAL;
        return (-1);
    }
    f->offset = (u_int)off;
    f->c = 0;
    return (off);
}