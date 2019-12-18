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
typedef  int uint32_t ;

/* Variables and functions */
 char* malloc (int) ; 

__attribute__((used)) static char *
prepare_buf(int size, uint32_t off)
{
	char *buf;

	buf = malloc(size);
	if (buf == NULL)
		return (buf);

	if (size == 1)
		buf[0] = off & 0xff;
	else if (size == 2) {
		buf[0] = (off >> 8) & 0xff;
		buf[1] = off & 0xff;
	}

	return (buf);
}