#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct serial {scalar_t__ fd; } ;
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINTR ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int POLL_INTERVAL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int TIMEOUT ; 
 int atoi (char*) ; 
 int connect (scalar_t__,struct sockaddr*,int) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 struct hostent* gethostbyname (char*) ; 
 int getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  net_close (struct serial*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ ui_loop_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
net_open (struct serial *scb, const char *name)
{
  char *port_str, hostname[100];
  int n, port, tmp;
  int use_udp;
  struct hostent *hostent;
  struct sockaddr_in sockaddr;

  use_udp = 0;
  if (strncmp (name, "udp:", 4) == 0)
    {
      use_udp = 1;
      name = name + 4;
    }
  else if (strncmp (name, "tcp:", 4) == 0)
    name = name + 4;

  port_str = strchr (name, ':');

  if (!port_str)
    error ("net_open: No colon in host name!");	   /* Shouldn't ever happen */

  tmp = min (port_str - name, (int) sizeof hostname - 1);
  strncpy (hostname, name, tmp);	/* Don't want colon */
  hostname[tmp] = '\000';	/* Tie off host name */
  port = atoi (port_str + 1);

  /* default hostname is localhost */
  if (!hostname[0])
    strcpy (hostname, "localhost");

  hostent = gethostbyname (hostname);
  if (!hostent)
    {
      fprintf_unfiltered (gdb_stderr, "%s: unknown host\n", hostname);
      errno = ENOENT;
      return -1;
    }

  if (use_udp)
    scb->fd = socket (PF_INET, SOCK_DGRAM, 0);
  else
    scb->fd = socket (PF_INET, SOCK_STREAM, 0);

  if (scb->fd < 0)
    return -1;
  
  sockaddr.sin_family = PF_INET;
  sockaddr.sin_port = htons (port);
  memcpy (&sockaddr.sin_addr.s_addr, hostent->h_addr,
	  sizeof (struct in_addr));

  /* set socket nonblocking */
  tmp = 1;
  ioctl (scb->fd, FIONBIO, &tmp);

  /* Use Non-blocking connect.  connect() will return 0 if connected already. */
  n = connect (scb->fd, (struct sockaddr *) &sockaddr, sizeof (sockaddr));

  if (n < 0 && errno != EINPROGRESS)
    {
      net_close (scb);
      return -1;
    }

  if (n)
    {
      /* looks like we need to wait for the connect */
      struct timeval t;
      fd_set rset, wset;
      int polls = 0;
      FD_ZERO (&rset);

      do 
	{
	  /* While we wait for the connect to complete 
	     poll the UI so it can update or the user can 
	     interrupt. */
	  if (ui_loop_hook)
	    {
	      if (ui_loop_hook (0))
		{
		  errno = EINTR;
		  net_close (scb);
		  return -1;
		}
	    }
	  
	  FD_SET (scb->fd, &rset);
	  wset = rset;
	  t.tv_sec = 0;
	  t.tv_usec = 1000000 / POLL_INTERVAL;
	  
	  n = select (scb->fd + 1, &rset, &wset, NULL, &t);
	  polls++;
	} 
      while (n == 0 && polls <= TIMEOUT * POLL_INTERVAL);
      if (n < 0 || polls > TIMEOUT * POLL_INTERVAL)
	{
	  if (polls > TIMEOUT * POLL_INTERVAL)
	    errno = ETIMEDOUT;
	  net_close (scb);
	  return -1;
	}
    }

  /* Got something.  Is it an error? */
  {
    int res, err, len;
    len = sizeof(err);
    res = getsockopt (scb->fd, SOL_SOCKET, SO_ERROR, &err, &len);
    if (res < 0 || err)
      {
	if (err)
	  errno = err;
	net_close (scb);
	return -1;
      }
  } 

  /* turn off nonblocking */
  tmp = 0;
  ioctl (scb->fd, FIONBIO, &tmp);

  if (use_udp == 0)
    {
      /* Disable Nagle algorithm. Needed in some cases. */
      tmp = 1;
      setsockopt (scb->fd, IPPROTO_TCP, TCP_NODELAY,
		  (char *)&tmp, sizeof (tmp));
    }

  /* If we don't do this, then GDB simply exits
     when the remote side dies.  */
  signal (SIGPIPE, SIG_IGN);

  return 0;
}