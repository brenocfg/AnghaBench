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
 int ENOBUFS ; 
 int ENOTCONN ; 
 int ETIMEDOUT ; 
 size_t MAX_SEND_SIZE ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SHUT_RD ; 
 scalar_t__ blocking_socket (int) ; 
 int errno ; 
 int /*<<< orphan*/  pjdlog_info (char*,int,char*) ; 
 int /*<<< orphan*/  pjdlog_warning (char*) ; 
 int proto_descriptor_send (int,int) ; 
 int send (int,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

int
proto_common_send(int sock, const unsigned char *data, size_t size, int fd)
{
	ssize_t done;
	size_t sendsize;
	int errcount = 0;

	PJDLOG_ASSERT(sock >= 0);

	if (data == NULL) {
		/* The caller is just trying to decide about direction. */

		PJDLOG_ASSERT(size == 0);

		if (shutdown(sock, SHUT_RD) == -1)
			return (errno);
		return (0);
	}

	PJDLOG_ASSERT(data != NULL);
	PJDLOG_ASSERT(size > 0);

	do {
		sendsize = size < MAX_SEND_SIZE ? size : MAX_SEND_SIZE;
		done = send(sock, data, sendsize, MSG_NOSIGNAL);
		if (done == 0) {
			return (ENOTCONN);
		} else if (done == -1) {
			if (errno == EINTR)
				continue;
			if (errno == ENOBUFS) {
				/*
				 * If there are no buffers we retry.
				 * After each try we increase delay before the
				 * next one and we give up after fifteen times.
				 * This gives 11s of total wait time.
				 */
				if (errcount == 15) {
					pjdlog_warning("Getting ENOBUFS errors for 11s on send(), giving up.");
				} else {
					if (errcount == 0)
						pjdlog_warning("Got ENOBUFS error on send(), retrying for a bit.");
					errcount++;
					usleep(100000 * errcount);
					continue;
				}
			}
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
		data += done;
		size -= done;
	} while (size > 0);
	if (errcount > 0) {
		pjdlog_info("Data sent successfully after %d ENOBUFS error%s.",
		    errcount, errcount == 1 ? "" : "s");
	}

	if (fd == -1)
		return (0);
	return (proto_descriptor_send(sock, fd));
}