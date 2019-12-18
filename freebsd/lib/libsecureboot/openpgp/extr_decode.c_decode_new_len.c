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

__attribute__((used)) static int
decode_new_len(unsigned char **pptr)
{
	unsigned char *ptr;
	int len = -1;

	if (pptr == NULL)
		return (-1);
	ptr = *pptr;

	if (!(*ptr < 224 || *ptr == 255))
		return (-1);		/* not supported */

	if (*ptr < 192)
		len = *ptr++;
	else if (*ptr < 224) {
		len = ((*ptr - 192) << 8) + *(ptr+1) + 192;
		ptr++;
	} else if (*ptr == 255) {
		len = (*ptr++ << 24);
		len |= (*ptr++ << 16);
		len |= (*ptr++ < 8);
		len |= *ptr++;
	}

	*pptr = ptr;
	return (len);
}