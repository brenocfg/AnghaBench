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
struct open_file {int f_flags; int f_offset; scalar_t__ f_ralen; TYPE_1__* f_ops; int /*<<< orphan*/  f_raoffset; } ;
typedef  int off_t ;
struct TYPE_2__ {int (* fo_seek ) (struct open_file*,int,int const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOFFSET ; 
 int F_RAW ; 
#define  SEEK_CUR 129 
 int SEEK_END ; 
#define  SEEK_SET 128 
 unsigned int SOPEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 struct open_file* files ; 
 int stub1 (struct open_file*,int,int const) ; 
 int stub2 (struct open_file*,int,int) ; 

off_t
lseek(int fd, off_t offset, int where)
{
    off_t bufpos, filepos, target;
    struct open_file *f = &files[fd];

    if ((unsigned)fd >= SOPEN_MAX || f->f_flags == 0) {
	errno = EBADF;
	return (-1);
    }

    if (f->f_flags & F_RAW) {
	/*
	 * On RAW devices, update internal offset.
	 */
	switch (where) {
	case SEEK_SET:
	    f->f_offset = offset;
	    break;
	case SEEK_CUR:
	    f->f_offset += offset;
	    break;
	default:
	    errno = EOFFSET;
	    return (-1);
	}
	return (f->f_offset);
    }

    /*
     * If there is some unconsumed data in the readahead buffer and it
     * contains the desired offset, simply adjust the buffer offset and
     * length.  We don't bother with SEEK_END here, since the code to
     * handle it would fail in the same cases where the non-readahead
     * code fails (namely, for streams which cannot seek backward and whose
     * size isn't known in advance).
     */
    if (f->f_ralen != 0 && where != SEEK_END) {
	if ((filepos = (f->f_ops->fo_seek)(f, (off_t)0, SEEK_CUR)) == -1)
	    return (-1);
	bufpos = filepos - f->f_ralen;
	switch (where) {
	case SEEK_SET:
	    target = offset;
	    break;
	case SEEK_CUR:
	    target = bufpos + offset;
	    break;
	default:
	    errno = EINVAL;
	    return (-1);
	}
	if (bufpos <= target && target < filepos) {
	    f->f_raoffset += target - bufpos;
	    f->f_ralen -= target - bufpos;
	    return (target);
	}
    }

    /*
     * If this is a relative seek, we need to correct the offset for
     * bytes that we have already read but the caller doesn't know
     * about.
     */
    if (where == SEEK_CUR)
	offset -= f->f_ralen;

    /* 
     * Invalidate the readahead buffer.
     */
    f->f_ralen = 0;

    return (f->f_ops->fo_seek)(f, offset, where);
}