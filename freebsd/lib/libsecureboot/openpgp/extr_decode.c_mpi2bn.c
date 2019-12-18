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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 

BIGNUM *
mpi2bn(unsigned char **pptr)
{
	BIGNUM *bn = NULL;
	unsigned char *ptr;
	int mlen;

	if (pptr == NULL)
		return (NULL);

	ptr = *pptr;

	mlen = (*ptr++ << 8);
	mlen |= *ptr++;			/* number of bits */
	mlen = (mlen + 7) / 8;		/* number of bytes */
	bn = BN_bin2bn(ptr, mlen, NULL);
	ptr += mlen;
	*pptr = ptr;

	return (bn);
}