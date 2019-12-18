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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  ng_hci_event_pkt_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int ERROR ; 
 scalar_t__ ETIMEDOUT ; 
 int FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  timeout ; 

int
hci_recv(int s, char *buffer, int *size)
{
	struct timeval	tv;
	fd_set		rfd;
	int		n;

	assert(buffer != NULL);
	assert(size != NULL);
	assert(*size > sizeof(ng_hci_event_pkt_t));

again:
	FD_ZERO(&rfd);
	FD_SET(s, &rfd);

	tv.tv_sec = timeout;
	tv.tv_usec = 0;

	n = select(s + 1, &rfd, NULL, NULL, &tv);
	if (n <= 0) {
		if (n < 0) {
			if (errno == EINTR)
				goto again;
		} else
			errno = ETIMEDOUT;

		return (ERROR);
	}

	assert(FD_ISSET(s, &rfd));

	n = recv(s, buffer, *size, 0);
	if (n < 0)
		return (ERROR);

	*size = n;

	return (OK);
}