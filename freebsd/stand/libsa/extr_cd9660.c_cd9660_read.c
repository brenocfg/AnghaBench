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
struct open_file {scalar_t__ f_fsdata; } ;
struct file {scalar_t__ f_off; scalar_t__ f_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int buf_read_file (struct open_file*,char**,size_t*) ; 

__attribute__((used)) static int
cd9660_read(struct open_file *f, void *start, size_t size, size_t *resid)
{
	struct file *fp = (struct file *)f->f_fsdata;
	char *buf, *addr;
	size_t buf_size, csize;
	int rc = 0;

	addr = start;
	while (size) {
		if (fp->f_off < 0 || fp->f_off >= fp->f_size)
			break;

		rc = buf_read_file(f, &buf, &buf_size);
		if (rc)
			break;

		csize = size > buf_size ? buf_size : size;
		bcopy(buf, addr, csize);

		fp->f_off += csize;
		addr += csize;
		size -= csize;
	}
	if (resid)
		*resid = size;
	return (rc);
}