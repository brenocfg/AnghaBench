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
struct file {scalar_t__ f_pos; scalar_t__ f_version; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  SEEK_CUR 132 
#define  SEEK_DATA 131 
#define  SEEK_END 130 
#define  SEEK_HOLE 129 
#define  SEEK_SET 128 

__attribute__((used)) static loff_t adi_llseek(struct file *file, loff_t offset, int whence)
{
	loff_t ret = -EINVAL;

	switch (whence) {
	case SEEK_END:
	case SEEK_DATA:
	case SEEK_HOLE:
		/* unsupported */
		return -EINVAL;
	case SEEK_CUR:
		if (offset == 0)
			return file->f_pos;

		offset += file->f_pos;
		break;
	case SEEK_SET:
		break;
	}

	if (offset != file->f_pos) {
		file->f_pos = offset;
		file->f_version = 0;
		ret = offset;
	}

	return ret;
}