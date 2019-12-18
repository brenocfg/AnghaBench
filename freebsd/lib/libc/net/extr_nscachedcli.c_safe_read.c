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
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct kevent {scalar_t__ filter; size_t data; int flags; } ;
struct cached_connection_ {int /*<<< orphan*/  sockfd; int /*<<< orphan*/  read_queue; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EVFILT_READ ; 
 int EV_EOF ; 
 int /*<<< orphan*/  NS_DEFAULT_CACHED_IO_TIMEOUT ; 
 int _kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 
 int _read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
safe_read(struct cached_connection_ *connection, void *data, size_t data_size)
{
	struct kevent eventlist;
	size_t result;
	ssize_t s_result;
	struct timespec timeout;
	int nevents;

	if (data_size == 0)
		return (0);

	timeout.tv_sec = NS_DEFAULT_CACHED_IO_TIMEOUT;
	timeout.tv_nsec = 0;
	result = 0;
	do {
		nevents = _kevent(connection->read_queue, NULL, 0, &eventlist,
		    1, &timeout);
		if (nevents == 1 && eventlist.filter == EVFILT_READ) {
			s_result = _read(connection->sockfd, data + result,
			    eventlist.data <= data_size - result ?
			    eventlist.data : data_size - result);
			if (s_result == -1)
				return (-1);
			else
				result += s_result;

			if (eventlist.flags & EV_EOF)
				return (result < data_size ? -1 : 0);
		} else
			return (-1);
	} while (result < data_size);

	return (0);
}