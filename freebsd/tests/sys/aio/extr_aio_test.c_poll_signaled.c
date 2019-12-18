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
struct aiocb {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EINPROGRESS 128 
 int /*<<< orphan*/  EINTR ; 
 int aio_error (struct aiocb*) ; 
 int aio_return (struct aiocb*) ; 
 int /*<<< orphan*/  completions ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
poll_signaled(struct aiocb *aio)
{
	int error;

	ATF_REQUIRE_EQ(0, sem_wait(&completions));
	error = aio_error(aio);
	switch (error) {
		case EINPROGRESS:
			errno = EINTR;
			return (-1);
		case 0:
			return (aio_return(aio));
		default:
			return (error);
	}
}