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
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int ENOTCONN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SHUT_WR ; 
 scalar_t__ blocking_socket (int) ; 
 int errno ; 
 int proto_descriptor_recv (int,int*) ; 
 int recv (int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int shutdown (int,int /*<<< orphan*/ ) ; 

int
proto_common_recv(int sock, unsigned char *data, size_t size, int *fdp)
{
	ssize_t done;

	PJDLOG_ASSERT(sock >= 0);

	if (data == NULL) {
		/* The caller is just trying to decide about direction. */

		PJDLOG_ASSERT(size == 0);

		if (shutdown(sock, SHUT_WR) == -1)
			return (errno);
		return (0);
	}

	PJDLOG_ASSERT(data != NULL);
	PJDLOG_ASSERT(size > 0);

	do {
		done = recv(sock, data, size, MSG_WAITALL);
	} while (done == -1 && errno == EINTR);
	if (done == 0) {
		return (ENOTCONN);
	} else if (done < 0) {
		/*
		 * If this is blocking socket and we got EAGAIN, this
		 * means the request timed out. Translate errno to
		 * ETIMEDOUT, to give administrator a hint to
		 * eventually increase timeout.
		 */
		if (errno == EAGAIN && blocking_socket(sock))
			errno = ETIMEDOUT;
		return (errno);
	}
	if (fdp == NULL)
		return (0);
	return (proto_descriptor_recv(sock, fdp));
}