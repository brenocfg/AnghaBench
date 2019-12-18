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

/* Variables and functions */
 int write (int,unsigned char*,size_t) ; 

__attribute__((used)) static int
block_write(int fd, void *buf, size_t len)
{
    unsigned char *p = buf;
    int b;
    while(len) {
	b = write(fd, p, len);
	if(b < 0)
	    return -1;
	len -= b;
	p += b;
    }
    return p - (unsigned char*)buf;
}