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
typedef  int uInt ;
struct z_file {scalar_t__ zf_dataoffset; } ;

/* Variables and functions */
 int COMMENT ; 
 int EXTRA_FIELD ; 
 int HEAD_CRC ; 
 int ORIG_NAME ; 
 int RESERVED ; 
 int Z_DEFLATED ; 
 int get_byte (struct z_file*,scalar_t__*) ; 
 int* gz_magic ; 

__attribute__((used)) static int
check_header(struct z_file *zf)
{
    int		method; /* method byte */
    int		flags;  /* flags byte */
    uInt	len;
    int		c;

    zf->zf_dataoffset = 0;
    /* Check the gzip magic header */
    for (len = 0; len < 2; len++) {
	c = get_byte(zf, &zf->zf_dataoffset);
	if (c != gz_magic[len]) {
	    return(1);
	}
    }
    method = get_byte(zf, &zf->zf_dataoffset);
    flags = get_byte(zf, &zf->zf_dataoffset);
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
	return(1);
    }
    
    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) (void)get_byte(zf, &zf->zf_dataoffset);

    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
	len  =  (uInt)get_byte(zf, &zf->zf_dataoffset);
	len += ((uInt)get_byte(zf, &zf->zf_dataoffset))<<8;
	/* len is garbage if EOF but the loop below will quit anyway */
	while (len-- != 0 && get_byte(zf, &zf->zf_dataoffset) != -1) ;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
	while ((c = get_byte(zf, &zf->zf_dataoffset)) != 0 && c != -1) ;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
	while ((c = get_byte(zf, &zf->zf_dataoffset)) != 0 && c != -1) ;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
	for (len = 0; len < 2; len++) c = get_byte(zf, &zf->zf_dataoffset);
    }
    /* if there's data left, we're in business */
    return((c == -1) ? 1 : 0);
}