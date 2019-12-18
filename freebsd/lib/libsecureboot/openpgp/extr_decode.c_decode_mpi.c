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

unsigned char *
decode_mpi(unsigned char **pptr, size_t *sz)
{
	unsigned char *data;
	unsigned char *ptr;
	size_t mlen;

	if (pptr == NULL || sz == NULL)
		return (NULL);

	ptr = *pptr;

	mlen = (size_t)(*ptr++ << 8);
	mlen |= (size_t)*ptr++;		/* number of bits */
	mlen = (mlen + 7) / 8;		/* number of bytes */
	*sz = mlen;
	data = ptr;
	ptr += mlen;
	*pptr = ptr;
	return (data);
}