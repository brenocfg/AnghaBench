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
 int /*<<< orphan*/  BYTE_COPY_FWD (unsigned long,unsigned long,size_t) ; 
 unsigned long OPSIZ ; 
 size_t OP_T_THRES ; 
 int /*<<< orphan*/  WORD_COPY_FWD (unsigned long,unsigned long,size_t,size_t) ; 

void *memcpy(void *dstpp, const void *srcpp, size_t len)
{
	unsigned long int dstp = (long int) dstpp;
	unsigned long int srcp = (long int) srcpp;

	/* Copy from the beginning to the end.  */

	/* If there not too few bytes to copy, use word copy.  */
	if (len >= OP_T_THRES) {
		/* Copy just a few bytes to make DSTP aligned.  */
		len -= (-dstp) % OPSIZ;
		BYTE_COPY_FWD(dstp, srcp, (-dstp) % OPSIZ);

		/* Copy whole pages from SRCP to DSTP by virtual address
		   manipulation, as much as possible.  */

		/* PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len); */

		/* Copy from SRCP to DSTP taking advantage of the known
		   alignment of DSTP. Number of bytes remaining is put in the
		   third argument, i.e. in LEN.  This number may vary from
		   machine to machine. */

		WORD_COPY_FWD(dstp, srcp, len, len);

		/* Fall out and copy the tail. */
	}

	/* There are just a few bytes to copy.  Use byte memory operations. */
	BYTE_COPY_FWD(dstp, srcp, len);

	return dstpp;
}