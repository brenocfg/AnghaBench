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
struct split_file {int tot_pos; int file_pos; int curfile; int filesc; int /*<<< orphan*/  curfd; } ;
struct open_file {scalar_t__ f_fsdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int errno ; 
 int read (int /*<<< orphan*/ ,void*,size_t) ; 
 int split_openfile (struct split_file*) ; 

__attribute__((used)) static int 
splitfs_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
    ssize_t nread;
    size_t totread;
    struct split_file *sf;

    sf = (struct split_file *)f->f_fsdata;
    totread = 0;
    do {
	nread = read(sf->curfd, buf, size - totread);

	/* Error? */
	if (nread == -1)
	    return (errno);

	sf->tot_pos += nread;
	sf->file_pos += nread;
	totread += nread;
	buf = (char *)buf + nread;

	if (totread < size) {				/* EOF */
	    if (sf->curfile == (sf->filesc - 1))	/* Last slice */
		break;

	    /* Close previous slice */
	    if (close(sf->curfd) != 0)
		return (errno);

	    sf->curfile++;
	    errno = split_openfile(sf);
	    if (errno)
		    return (errno);
	}
    } while (totread < size);

    if (resid != NULL)
	*resid = size - totread;

    return (0);
}