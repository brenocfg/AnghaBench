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
struct TYPE_2__ {size_t avail_out; scalar_t__ avail_in; char* msg; void* next_out; } ;
struct z_file {int zf_endseen; TYPE_1__ zf_zstream; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int EIO ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int zf_fill (struct z_file*) ; 

__attribute__((used)) static int 
zf_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
    struct z_file	*zf = (struct z_file *)f->f_fsdata;
    int			error;

    zf->zf_zstream.next_out = buf;			/* where and how much */
    zf->zf_zstream.avail_out = size;

    while (zf->zf_zstream.avail_out && zf->zf_endseen == 0) {
	if ((zf->zf_zstream.avail_in == 0) && (zf_fill(zf) == -1)) {
	    printf("zf_read: fill error\n");
	    return(EIO);
	}
	if (zf->zf_zstream.avail_in == 0) {		/* oops, unexpected EOF */
	    printf("zf_read: unexpected EOF\n");
	    if (zf->zf_zstream.avail_out == size)
		return(EIO);
	    break;
	}

	error = inflate(&zf->zf_zstream, Z_SYNC_FLUSH);	/* decompression pass */
	if (error == Z_STREAM_END) {			/* EOF, all done */
	    zf->zf_endseen = 1;
	    break;
	}
	if (error != Z_OK) {				/* argh, decompression error */
	    printf("inflate: %s\n", zf->zf_zstream.msg);
	    return(EIO);
	}
    }
    if (resid != NULL)
	*resid = zf->zf_zstream.avail_out;
    return(0);
}