#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long* fds_bits; } ;
typedef  TYPE_1__ fd_set ;
typedef  unsigned long fd_mask ;

/* Variables and functions */
 int FD_SETSIZE ; 
 scalar_t__ NFDBITS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ffsl (unsigned long) ; 
 int /*<<< orphan*/  svc_getreq_common (int) ; 

void
svc_getreqset(fd_set *readfds)
{
	int bit, fd;
	fd_mask mask, *maskp;
	int sock;

	assert(readfds != NULL);

	maskp = readfds->fds_bits;
	for (sock = 0; sock < FD_SETSIZE; sock += NFDBITS) {
	    for (mask = *maskp++; (bit = ffsl(mask)) != 0;
		mask ^= (1ul << (bit - 1))) {
		/* sock has input waiting */
		fd = sock + bit - 1;
		svc_getreq_common(fd);
	    }
	}
}