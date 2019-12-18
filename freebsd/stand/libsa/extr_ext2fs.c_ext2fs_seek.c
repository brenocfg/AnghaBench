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
struct open_file {scalar_t__ f_fsdata; } ;
struct TYPE_2__ {int di_size; } ;
struct file {int f_seekp; TYPE_1__ f_di; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static off_t
ext2fs_seek(struct open_file *f, off_t offset, int where)
{
	struct file *fp = (struct file *)f->f_fsdata;

	switch (where) {
	case SEEK_SET:
		fp->f_seekp = offset;
		break;
	case SEEK_CUR:
		fp->f_seekp += offset;
		break;
	case SEEK_END:
		fp->f_seekp = fp->f_di.di_size - offset;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
	return (fp->f_seekp);
}