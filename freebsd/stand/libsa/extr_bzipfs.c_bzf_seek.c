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
struct TYPE_2__ {int total_out_lo32; } ;
struct bz_file {TYPE_1__ bzf_bzstream; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  discard ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EOFFSET ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 
 scalar_t__ bzf_read (struct open_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bzf_rewind (struct open_file*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static off_t
bzf_seek(struct open_file *f, off_t offset, int where)
{
    struct bz_file	*bzf = (struct bz_file *)f->f_fsdata;
    off_t		target;
    char		discard[16];
    
    switch (where) {
    case SEEK_SET:
	target = offset;
	break;
    case SEEK_CUR:
	target = offset + bzf->bzf_bzstream.total_out_lo32;
	break;
    default:
	errno = EINVAL;
	return(-1);
    }

    /* Can we get there from here? */
    if (target < bzf->bzf_bzstream.total_out_lo32 && bzf_rewind(f) != 0) {
	errno = EOFFSET;
	return -1;
    }

    /* if bzf_rewind was called then bzf has changed */
    bzf = (struct bz_file *)f->f_fsdata;

    /* skip forwards if required */
    while (target > bzf->bzf_bzstream.total_out_lo32) {
	errno = bzf_read(f, discard, min(sizeof(discard),
	    target - bzf->bzf_bzstream.total_out_lo32), NULL);
	if (errno)
	    return(-1);
    }
    /* This is where we are (be honest if we overshot) */
    return(bzf->bzf_bzstream.total_out_lo32);
}