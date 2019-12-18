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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr ;

/* Variables and functions */
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int accept (int,struct sockaddr*,int*) ; 
 int atoi (char*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int remote_desc ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
remote_open (char *name)
{
  if (!strchr (name, ':'))
    {
      fprintf (stderr, "%s: Must specify tcp connection as host:addr\n", name);
      fflush (stderr);
      exit (1);
    }
  else
    {
      char *port_str;
      int port;
      struct sockaddr_in sockaddr;
      int tmp;
      int tmp_desc;

      port_str = strchr (name, ':');

      port = atoi (port_str + 1);

      tmp_desc = socket (PF_INET, SOCK_STREAM, 0);
      if (tmp_desc < 0)
	perror_with_name ("Can't open socket");

      /* Allow rapid reuse of this port. */
      tmp = 1;
      setsockopt (tmp_desc, SOL_SOCKET, SO_REUSEADDR, (char *) &tmp,
		  sizeof (tmp));

      sockaddr.sin_family = PF_INET;
      sockaddr.sin_port = htons (port);
      sockaddr.sin_addr.s_addr = INADDR_ANY;

      if (bind (tmp_desc, (struct sockaddr *) &sockaddr, sizeof (sockaddr))
	  || listen (tmp_desc, 1))
	perror_with_name ("Can't bind address");

      tmp = sizeof (sockaddr);
      remote_desc = accept (tmp_desc, (struct sockaddr *) &sockaddr, &tmp);
      if (remote_desc == -1)
	perror_with_name ("Accept failed");

      /* Enable TCP keep alive process. */
      tmp = 1;
      setsockopt (tmp_desc, SOL_SOCKET, SO_KEEPALIVE, (char *) &tmp, sizeof (tmp));

      /* Tell TCP not to delay small packets.  This greatly speeds up
         interactive response. */
      tmp = 1;
      setsockopt (remote_desc, IPPROTO_TCP, TCP_NODELAY,
		  (char *) &tmp, sizeof (tmp));

      close (tmp_desc);		/* No longer need this */

      signal (SIGPIPE, SIG_IGN);	/* If we don't do this, then gdbreplay simply
					   exits when the remote side dies.  */
    }

  fcntl (remote_desc, F_SETFL, FASYNC);

  fprintf (stderr, "Replay logfile using %s\n", name);
  fflush (stderr);
}