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
struct bz_file {int bzf_buf; TYPE_1__ bzf_bzstream; int /*<<< orphan*/  bzf_rawfd; } ;

/* Variables and functions */
 int BZ_BUFSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int,int) ; 
 int read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bzf_fill(struct bz_file *bzf)
{
    int		result;
    int		req;
    
    req = BZ_BUFSIZE - bzf->bzf_bzstream.avail_in;
    result = 0;
    
    /* If we need more */
    if (req > 0) {
	/* move old data to bottom of buffer */
	if (req < BZ_BUFSIZE)
	    bcopy(bzf->bzf_buf + req, bzf->bzf_buf, BZ_BUFSIZE - req);
	
	/* read to fill buffer and update availibility data */
	result = read(bzf->bzf_rawfd, bzf->bzf_buf + bzf->bzf_bzstream.avail_in, req);
	bzf->bzf_bzstream.next_in = bzf->bzf_buf;
	if (result >= 0)
	    bzf->bzf_bzstream.avail_in += result;
    }
    return(result);
}