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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct fd_set {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int,struct fd_set*) ; 
 int /*<<< orphan*/  FD_ZERO (struct fd_set*) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 scalar_t__ select (int,struct fd_set*,struct fd_set*,struct fd_set*,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_fired ; 

__attribute__((used)) static int
try_connect(struct sockaddr_in *sin)
{
	struct 
	fd_set read_set;
	int i, s;

	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s < 0)
		err(-1, "socket(PF_INET, SOCK_STREAM)");

	i = 1;
	if (fcntl(s, F_SETFL, FIONBIO, &i) < 0)
		err(-1, "fcntl(s, FIOBIO, 1)");

	FD_ZERO(&read_set);
	FD_SET(s, &read_set);

	if (connect(s, (struct sockaddr *)sin, sizeof(*sin)) < 0 &&
	    errno != EINPROGRESS)
		err(-1, "connect(%s)", inet_ntoa(sin->sin_addr));

	if (select(s + 1, &read_set, &read_set, &read_set, NULL) < 0) {
		if ((errno == EINTR && !timer_fired) || (errno != EINTR))
			err(-1, "select");
		return (-1);
	}

	close(s);
	return (0);
}