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
typedef  int /*<<< orphan*/  ioctl_t ;

/* Variables and functions */
#define  EAGAIN 130 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  FIONBIO ; 
 int FNBIO ; 
 int FNDELAY ; 
 int FNDLEAY ; 
 int FNONBIO ; 
 int FNONBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NDELAY ; 
 int O_NONBLOCK ; 
 int _FNBIO ; 
 int _FNDELAY ; 
 int _FNONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fixio(int fd, int e)
{
    switch (e) {
    case -1:	/* Make sure that the code is reachable */

#ifdef EWOULDBLOCK
    case EWOULDBLOCK:
# define FDRETRY
#endif /* EWOULDBLOCK */

#if defined(POSIX) && defined(EAGAIN)
# if !defined(EWOULDBLOCK) || EWOULDBLOCK != EAGAIN
    case EAGAIN:
#  define FDRETRY
# endif /* !EWOULDBLOCK || EWOULDBLOCK != EAGAIN */
#endif /* POSIX && EAGAIN */

	e = -1;
#ifdef FDRETRY
# ifdef F_SETFL
/*
 * Great! we have on suns 3 flavors and 5 names...
 * I hope that will cover everything.
 * I added some more defines... many systems have different defines.
 * Rather than dealing with getting the right includes, we'll just
 * cover all the known possibilities here.  -- sterling@netcom.com
 */
#  ifndef O_NONBLOCK
#   define O_NONBLOCK 0
#  endif /* O_NONBLOCK */
#  ifndef O_NDELAY
#   define O_NDELAY 0
#  endif /* O_NDELAY */
#  ifndef FNBIO
#   define FNBIO 0
#  endif /* FNBIO */
#  ifndef _FNBIO
#   define _FNBIO 0
#  endif /* _FNBIO */
#  ifndef FNONBIO
#   define FNONBIO 0
#  endif /* FNONBIO */
#  ifndef FNONBLOCK
#   define FNONBLOCK 0
#  endif /* FNONBLOCK */
#  ifndef _FNONBLOCK
#   define _FNONBLOCK 0
#  endif /* _FNONBLOCK */
#  ifndef FNDELAY
#   define FNDELAY 0
#  endif /* FNDELAY */
#  ifndef _FNDELAY
#   define _FNDELAY 0
#  endif /* _FNDELAY */
#  ifndef FNDLEAY	/* Some linux versions have this typo */
#   define FNDLEAY 0
#  endif /* FNDLEAY */
	if ((e = fcntl(fd, F_GETFL, 0)) == -1)
	    return -1;

	e &= ~(O_NDELAY|O_NONBLOCK|FNBIO|_FNBIO|FNONBIO|FNONBLOCK|_FNONBLOCK|
	       FNDELAY|_FNDELAY|FNDLEAY);	/* whew! */
	if (fcntl(fd, F_SETFL, e) == -1)
	    return -1;
	else 
	    e = 0;
# endif /* F_SETFL */

# ifdef FIONBIO
	e = 0;
	if (ioctl(fd, FIONBIO, (ioctl_t) &e) == -1)
	    return -1;
# endif	/* FIONBIO */

#endif /* FDRETRY */
	return e;

    case EINTR:
	return 0;

    default:
	return -1;
    }
}