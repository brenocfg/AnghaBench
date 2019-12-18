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
 int ENAMETOOLONG ; 

int
copystr(const void * __restrict kfaddr, void * __restrict kdaddr, size_t len,
    size_t * __restrict lencopied)
{
	const char *src;
	size_t pos;
	char *dst;
	int error;

	error = ENAMETOOLONG;
	src = kfaddr;
	dst = kdaddr;
	for (pos = 0; pos < len; pos++) {
		dst[pos] = src[pos];
		if (src[pos] == '\0') {
			/* Increment pos to hold the number of bytes copied */
			pos++;
			error = 0;
			break;
		}
	}

	if (lencopied != NULL)
		*lencopied = pos;

	return (error);
}