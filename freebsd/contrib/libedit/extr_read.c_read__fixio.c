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

/* Variables and functions */
#define  EAGAIN 130 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NDELAY ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
read__fixio(int fd __attribute__((__unused__)), int e)
{

	switch (e) {
	case -1:		/* Make sure that the code is reachable */

#ifdef EWOULDBLOCK
	case EWOULDBLOCK:
#ifndef TRY_AGAIN
#define TRY_AGAIN
#endif
#endif /* EWOULDBLOCK */

#if defined(POSIX) && defined(EAGAIN)
#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
	case EAGAIN:
#ifndef TRY_AGAIN
#define TRY_AGAIN
#endif
#endif /* EWOULDBLOCK && EWOULDBLOCK != EAGAIN */
#endif /* POSIX && EAGAIN */

		e = 0;
#ifdef TRY_AGAIN
#if defined(F_SETFL) && defined(O_NDELAY)
		if ((e = fcntl(fd, F_GETFL, 0)) == -1)
			return -1;

		if (fcntl(fd, F_SETFL, e & ~O_NDELAY) == -1)
			return -1;
		else
			e = 1;
#endif /* F_SETFL && O_NDELAY */

#ifdef FIONBIO
		{
			int zero = 0;

			if (ioctl(fd, FIONBIO, &zero) == -1)
				return -1;
			else
				e = 1;
		}
#endif /* FIONBIO */

#endif /* TRY_AGAIN */
		return e ? 0 : -1;

	case EINTR:
		return 0;

	default:
		return -1;
	}
}