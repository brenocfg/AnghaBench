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
 int /*<<< orphan*/  BIO_F_BIO_SOCKET_NBIO ; 
 int BIO_socket_ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  FIONBIO ; 
 int FNDELAY ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SYS_F_FCNTL ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_last_sys_error () ; 

int BIO_socket_nbio(int s, int mode)
{
    int ret = -1;
    int l;

    l = mode;
# ifdef FIONBIO
    l = mode;

    ret = BIO_socket_ioctl(s, FIONBIO, &l);
# elif defined(F_GETFL) && defined(F_SETFL) && (defined(O_NONBLOCK) || defined(FNDELAY))
    /* make sure this call always pushes an error level; BIO_socket_ioctl() does so, so we do too. */

    l = fcntl(s, F_GETFL, 0);
    if (l == -1) {
        SYSerr(SYS_F_FCNTL, get_last_sys_error());
        ret = -1;
    } else {
#  if defined(O_NONBLOCK)
        l &= ~O_NONBLOCK;
#  else
        l &= ~FNDELAY; /* BSD4.x */
#  endif
        if (mode) {
#  if defined(O_NONBLOCK)
            l |= O_NONBLOCK;
#  else
            l |= FNDELAY; /* BSD4.x */
#  endif
        }
        ret = fcntl(s, F_SETFL, l);

        if (ret < 0) {
            SYSerr(SYS_F_FCNTL, get_last_sys_error());
        }
    }
# else
    /* make sure this call always pushes an error level; BIO_socket_ioctl() does so, so we do too. */
    BIOerr(BIO_F_BIO_SOCKET_NBIO, ERR_R_PASSED_INVALID_ARGUMENT);
# endif

    return (ret == 0);
}