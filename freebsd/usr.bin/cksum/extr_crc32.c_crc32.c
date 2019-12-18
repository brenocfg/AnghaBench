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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  CRC (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  crc32_total ; 
 int read (int,char*,int) ; 

int
crc32(int fd, uint32_t *cval, off_t *clen)
{
    uint32_t lcrc = ~0;
    int nr ;
    off_t len ;
    char buf[BUFSIZ], *p ;
	
    len = 0 ;
    crc32_total = ~crc32_total ;
    while ((nr = read(fd, buf, sizeof(buf))) > 0)
        for (len += nr, p = buf; nr--; ++p) {
	    CRC(lcrc, *p) ;
	    CRC(crc32_total, *p) ;
	}
    if (nr < 0)
        return 1 ;

    *clen = len ;
    *cval = ~lcrc ;
    crc32_total = ~crc32_total ;
    return 0 ;
}