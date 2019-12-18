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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ECONNABORTED ; 
 int ECONNRESET ; 
 int ENETRESET ; 
 int ENOTCONN ; 
 int ENOTSOCK ; 
 int ESHUTDOWN ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  MSG_PEEK ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int POLLRDBAND ; 
 int POLLRDNORM ; 
 int POLLWRBAND ; 
 int POLLWRNORM ; 
 int errno ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compute_revents (int fd, int sought, fd_set *rfds, fd_set *wfds, fd_set *efds)
{
  int happened = 0;
  if (FD_ISSET (fd, rfds))
    {
      int r;
      int socket_errno;

# if defined __MACH__ && defined __APPLE__
      /* There is a bug in Mac OS X that causes it to ignore MSG_PEEK
	 for some kinds of descriptors.  Detect if this descriptor is a
	 connected socket, a server socket, or something else using a
	 0-byte recv, and use ioctl(2) to detect POLLHUP.  */
      r = recv (fd, NULL, 0, MSG_PEEK);
      socket_errno = (r < 0) ? errno : 0;
      if (r == 0 || socket_errno == ENOTSOCK)
	ioctl (fd, FIONREAD, &r);
# else
      char data[64];
      r = recv (fd, data, sizeof (data), MSG_PEEK);
      socket_errno = (r < 0) ? errno : 0;
# endif
      if (r == 0)
	happened |= POLLHUP;

      /* If the event happened on an unconnected server socket,
	 that's fine. */
      else if (r > 0 || ( /* (r == -1) && */ socket_errno == ENOTCONN))
	happened |= (POLLIN | POLLRDNORM) & sought;

      /* Distinguish hung-up sockets from other errors.  */
      else if (socket_errno == ESHUTDOWN || socket_errno == ECONNRESET
	       || socket_errno == ECONNABORTED || socket_errno == ENETRESET)
	happened |= POLLHUP;

      /* some systems can't use recv() on non-socket, including HP NonStop */
      else if (/* (r == -1) && */ socket_errno == ENOTSOCK)
	happened |= (POLLIN | POLLRDNORM) & sought;

      else
	happened |= POLLERR;
    }

  if (FD_ISSET (fd, wfds))
    happened |= (POLLOUT | POLLWRNORM | POLLWRBAND) & sought;

  if (FD_ISSET (fd, efds))
    happened |= (POLLPRI | POLLRDBAND) & sought;

  return happened;
}