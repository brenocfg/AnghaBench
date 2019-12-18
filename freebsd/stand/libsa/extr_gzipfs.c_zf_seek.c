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
struct TYPE_2__ {int total_out; } ;
struct z_file {TYPE_1__ zf_zstream; } ;
struct open_file {scalar_t__ f_fsdata; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  discard ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 
 scalar_t__ errno ; 
 int /*<<< orphan*/  min (int,int) ; 
 scalar_t__ zf_read (struct open_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zf_rewind (struct open_file*) ; 

__attribute__((used)) static off_t
zf_seek(struct open_file *f, off_t offset, int where)
{
    struct z_file	*zf = (struct z_file *)f->f_fsdata;
    off_t		target;
    char		discard[16];
    
    switch (where) {
    case SEEK_SET:
	target = offset;
	break;
    case SEEK_CUR:
	target = offset + zf->zf_zstream.total_out;
	break;
    default:
	errno = EINVAL;
	return(-1);
    }

    /* rewind if required */
    if (target < zf->zf_zstream.total_out && zf_rewind(f) != 0)
	return(-1);

    /* skip forwards if required */
    while (target > zf->zf_zstream.total_out) {
	errno = zf_read(f, discard, min(sizeof(discard),
	    target - zf->zf_zstream.total_out), NULL);
	if (errno)
	    return(-1);
    }
    /* This is where we are (be honest if we overshot) */
    return(zf->zf_zstream.total_out);
}