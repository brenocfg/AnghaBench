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
struct TYPE_2__ {int next_in; int avail_in; } ;
struct bz_file {TYPE_1__ bzf_bzstream; } ;

/* Variables and functions */
 int* bz_magic ; 
 int get_byte (struct bz_file*) ; 

__attribute__((used)) static int
check_header(struct bz_file *bzf)
{
    unsigned int len;
    int		 c;

    /* Check the bzip2 magic header */
    for (len = 0; len < 3; len++) {
	c = get_byte(bzf);
	if (c != bz_magic[len]) {
	    return(1);
	}
    }
    /* Check that the block size is valid */
    c = get_byte(bzf);
    if (c < '1' || c > '9')
	return(1);

    /* Put back bytes that we've took from the input stream */
    bzf->bzf_bzstream.next_in -= 4;
    bzf->bzf_bzstream.avail_in += 4;

    return(0);
}