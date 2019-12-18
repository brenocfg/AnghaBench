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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int NUMCYCLES ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ message_recv (int) ; 
 scalar_t__ message_send (int) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static struct timespec
juggle(int fd1, int fd2, int pipeline)
{
	struct timespec tstart, tfinish;
	int i, j;

	if (clock_gettime(CLOCK_REALTIME, &tstart) < 0)
		err(-1, "juggle: clock_gettime");

	for (i = 0; i < NUMCYCLES; i++) {

		for (j = 0; j < pipeline; j++) {
			if (message_send(fd1) < 0)
				err(-1, "message_send fd1");
		}

		for (j = 0; j < pipeline; j++) {
			if (message_recv(fd2) < 0)
				err(-1, "message_recv fd2");

			if (message_send(fd2) < 0)
				err(-1, "message_send fd2");
		}

		for (j = 0; j < pipeline; j++) {
			if (message_recv(fd1) < 0)
				err(-1, "message_recv fd1");
		}
	}

	if (clock_gettime(CLOCK_REALTIME, &tfinish) < 0)
		err(-1, "juggle: clock_gettime");

	timespecsub(&tfinish, &tstart, &tfinish);

	return (tfinish);
}