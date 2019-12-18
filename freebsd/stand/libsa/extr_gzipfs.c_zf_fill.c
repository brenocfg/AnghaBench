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
struct TYPE_2__ {int avail_in; int next_in; } ;
struct z_file {int zf_buf; TYPE_1__ zf_zstream; int /*<<< orphan*/  zf_rawfd; } ;

/* Variables and functions */
 int Z_BUFSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int,int) ; 
 int read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
zf_fill(struct z_file *zf)
{
    int		result;
    int		req;
    
    req = Z_BUFSIZE - zf->zf_zstream.avail_in;
    result = 0;
    
    /* If we need more */
    if (req > 0) {
	/* move old data to bottom of buffer */
	if (req < Z_BUFSIZE)
	    bcopy(zf->zf_buf + req, zf->zf_buf, Z_BUFSIZE - req);
	
	/* read to fill buffer and update availibility data */
	result = read(zf->zf_rawfd, zf->zf_buf + zf->zf_zstream.avail_in, req);
	zf->zf_zstream.next_in = zf->zf_buf;
	if (result >= 0)
	    zf->zf_zstream.avail_in += result;
    }
    return(result);
}