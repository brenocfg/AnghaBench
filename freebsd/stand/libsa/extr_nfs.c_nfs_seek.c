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
typedef  int uint32_t ;
struct open_file {scalar_t__ f_fsdata; } ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
struct TYPE_4__ {TYPE_1__ fa_size; } ;
struct nfs_iodesc {int off; TYPE_2__ fa; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 
 int ntohl (int /*<<< orphan*/ ) ; 

off_t
nfs_seek(struct open_file *f, off_t offset, int where)
{
	struct nfs_iodesc *d = (struct nfs_iodesc *)f->f_fsdata;
	uint32_t size = ntohl(d->fa.fa_size.val[1]);

	switch (where) {
	case SEEK_SET:
		d->off = offset;
		break;
	case SEEK_CUR:
		d->off += offset;
		break;
	case SEEK_END:
		d->off = size - offset;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}

	return (d->off);
}