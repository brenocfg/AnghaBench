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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 int EBADF ; 
 int EFAULT ; 
 int NBBY ; 
 int NFDBITS ; 
 int fubyte (char*) ; 
 int rounddown (int,int) ; 

__attribute__((used)) static int
select_check_badfd(fd_set *fd_in, int nd, int ndu, int abi_nfdbits)
{
	char *addr, *oaddr;
	int b, i, res;
	uint8_t bits;

	if (nd >= ndu || fd_in == NULL)
		return (0);

	oaddr = NULL;
	bits = 0; /* silence gcc */
	for (i = nd; i < ndu; i++) {
		b = i / NBBY;
#if BYTE_ORDER == LITTLE_ENDIAN
		addr = (char *)fd_in + b;
#else
		addr = (char *)fd_in;
		if (abi_nfdbits == NFDBITS) {
			addr += rounddown(b, sizeof(fd_mask)) +
			    sizeof(fd_mask) - 1 - b % sizeof(fd_mask);
		} else {
			addr += rounddown(b, sizeof(uint32_t)) +
			    sizeof(uint32_t) - 1 - b % sizeof(uint32_t);
		}
#endif
		if (addr != oaddr) {
			res = fubyte(addr);
			if (res == -1)
				return (EFAULT);
			oaddr = addr;
			bits = res;
		}
		if ((bits & (1 << (i % NBBY))) != 0)
			return (EBADF);
	}
	return (0);
}