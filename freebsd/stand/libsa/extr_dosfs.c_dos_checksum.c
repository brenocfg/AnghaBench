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
 int /*<<< orphan*/  bcopy (unsigned char*,char*,int) ; 

__attribute__((used)) static int
dos_checksum(unsigned char *name, unsigned char *ext)
{
    int x, i;
    char buf[11];

    bcopy(name, buf, 8);
    bcopy(ext, buf+8, 3);
    x = 0;
    for (i = 0; i < 11; i++) {
	x = ((x & 1) << 7) | (x >> 1);
	x += buf[i];
	x &= 0xff;
    }
    return (x);
}