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
struct ber {size_t br_rend; size_t br_rptr; int /*<<< orphan*/ * br_rbuf; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 size_t MINIMUM (size_t,size_t) ; 
 int /*<<< orphan*/  bcopy (size_t,void*,size_t) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static ssize_t
ber_readbuf(struct ber *b, void *buf, size_t nbytes)
{
	size_t	 sz;
	size_t	 len;

	if (b->br_rbuf == NULL)
		return -1;

	sz = b->br_rend - b->br_rptr;
	len = MINIMUM(nbytes, sz);
	if (len == 0) {
		errno = ECANCELED;
		return (-1);	/* end of buffer and parser wants more data */
	}

	bcopy(b->br_rptr, buf, len);
	b->br_rptr += len;

	return (len);
}