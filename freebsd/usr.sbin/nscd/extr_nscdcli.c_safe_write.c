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
struct nscd_connection_ {int /*<<< orphan*/  sockfd; int /*<<< orphan*/  write_queue; } ;
struct kevent {scalar_t__ filter; int flags; scalar_t__ data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_NSCD_IO_TIMEOUT ; 
 scalar_t__ EVFILT_WRITE ; 
 int EV_EOF ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 
 int write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
safe_write(struct nscd_connection_ *connection, const void *data,
	size_t data_size)
{
	struct kevent eventlist;
	int	nevents;
	size_t result;
	ssize_t s_result;
	struct timespec	timeout;

	if (data_size == 0)
		return (0);

	timeout.tv_sec = DEFAULT_NSCD_IO_TIMEOUT;
	timeout.tv_nsec = 0;
	result = 0;
	do {
		nevents = kevent(connection->write_queue, NULL, 0, &eventlist,
	    		1, &timeout);
		if ((nevents == 1) && (eventlist.filter == EVFILT_WRITE)) {
			s_result = write(connection->sockfd,
				(char *)data + result,
				(size_t)eventlist.data < data_size - result ?
		    		(size_t)eventlist.data : data_size - result);
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