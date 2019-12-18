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
struct ib_user_mad {int agent_id; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int,int,...) ; 
 int EINVAL ; 
 int EIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  TRACE (char*,int,void*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (void*,int) ; 
 int dev_poll (int,int) ; 
 int errno ; 
 int read (int,void*,int) ; 
 int umad_size () ; 

int umad_recv(int fd, void *umad, int *length, int timeout_ms)
{
	struct ib_user_mad *mad = umad;
	int n;

	errno = 0;
	TRACE("fd %d umad %p timeout %u", fd, umad, timeout_ms);

	if (!umad || !length) {
		errno = EINVAL;
		return -EINVAL;
	}

	if (timeout_ms && (n = dev_poll(fd, timeout_ms)) < 0) {
		if (!errno)
			errno = -n;
		return n;
	}

	n = read(fd, umad, umad_size() + *length);

	VALGRIND_MAKE_MEM_DEFINED(umad, umad_size() + *length);

	if ((n >= 0) && (n <= umad_size() + *length)) {
		DEBUG("mad received by agent %d length %d", mad->agent_id, n);
		if (n > umad_size())
			*length = n - umad_size();
		else
			*length = 0;
		return mad->agent_id;
	}

	if (n == -EWOULDBLOCK) {
		if (!errno)
			errno = EWOULDBLOCK;
		return n;
	}

	DEBUG("read returned %zu > sizeof umad %zu + length %d (%m)",
	      mad->length - umad_size(), umad_size(), *length);

	*length = mad->length - umad_size();
	if (!errno)
		errno = EIO;
	return -errno;
}