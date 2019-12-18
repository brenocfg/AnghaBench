#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union sockunion {scalar_t__ su_family; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sizebuf ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  hostbuf ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int /*<<< orphan*/  su_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  su_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  su_len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EADDRINUSE ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int IPTOS_THROUGHPUT ; 
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int O_NONBLOCK ; 
 scalar_t__ TYPE_A ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ byte_count ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 TYPE_4__ ctrl_addr ; 
 int data ; 
 TYPE_1__ data_dest ; 
 TYPE_2__ data_source ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int file_size ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getdatasock (char*) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 TYPE_1__ his_addr ; 
 int pdata ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 scalar_t__ swaitint ; 
 int swaitmax ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ type ; 
 int usedefault ; 

__attribute__((used)) static FILE *
dataconn(char *name, off_t size, char *mode)
{
	char sizebuf[32];
	FILE *file;
	int retry = 0, tos, conerrno;

	file_size = size;
	byte_count = 0;
	if (size != -1)
		(void) snprintf(sizebuf, sizeof(sizebuf),
				" (%jd bytes)", (intmax_t)size);
	else
		*sizebuf = '\0';
	if (pdata >= 0) {
		union sockunion from;
		socklen_t fromlen = ctrl_addr.su_len;
		int flags, s;
		struct timeval timeout;
		fd_set set;

		FD_ZERO(&set);
		FD_SET(pdata, &set);

		timeout.tv_usec = 0;
		timeout.tv_sec = 120;

		/*
		 * Granted a socket is in the blocking I/O mode,
		 * accept() will block after a successful select()
		 * if the selected connection dies in between.
		 * Therefore set the non-blocking I/O flag here.
		 */
		if ((flags = fcntl(pdata, F_GETFL, 0)) == -1 ||
		    fcntl(pdata, F_SETFL, flags | O_NONBLOCK) == -1)
			goto pdata_err;
		if (select(pdata+1, &set, NULL, NULL, &timeout) <= 0 ||
		    (s = accept(pdata, (struct sockaddr *) &from, &fromlen)) < 0)
			goto pdata_err;
		(void) close(pdata);
		pdata = s;
		/*
		 * Unset the inherited non-blocking I/O flag
		 * on the child socket so stdio can work on it.
		 */
		if ((flags = fcntl(pdata, F_GETFL, 0)) == -1 ||
		    fcntl(pdata, F_SETFL, flags & ~O_NONBLOCK) == -1)
			goto pdata_err;
#ifdef IP_TOS
		if (from.su_family == AF_INET)
	      {
		tos = IPTOS_THROUGHPUT;
		if (setsockopt(s, IPPROTO_IP, IP_TOS, &tos, sizeof(int)) < 0)
			syslog(LOG_WARNING, "pdata setsockopt (IP_TOS): %m");
	      }
#endif
		reply(150, "Opening %s mode data connection for '%s'%s.",
		     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
		return (fdopen(pdata, mode));
pdata_err:
		reply(425, "Can't open data connection.");
		(void) close(pdata);
		pdata = -1;
		return (NULL);
	}
	if (data >= 0) {
		reply(125, "Using existing data connection for '%s'%s.",
		    name, sizebuf);
		usedefault = 1;
		return (fdopen(data, mode));
	}
	if (usedefault)
		data_dest = his_addr;
	usedefault = 1;
	do {
		file = getdatasock(mode);
		if (file == NULL) {
			char hostbuf[NI_MAXHOST], portbuf[NI_MAXSERV];

			if (getnameinfo((struct sockaddr *)&data_source,
				data_source.su_len,
				hostbuf, sizeof(hostbuf) - 1,
				portbuf, sizeof(portbuf) - 1,
				NI_NUMERICHOST|NI_NUMERICSERV))
					*hostbuf = *portbuf = 0;
			hostbuf[sizeof(hostbuf) - 1] = 0;
			portbuf[sizeof(portbuf) - 1] = 0;
			reply(425, "Can't create data socket (%s,%s): %s.",
				hostbuf, portbuf, strerror(errno));
			return (NULL);
		}
		data = fileno(file);
		conerrno = 0;
		if (connect(data, (struct sockaddr *)&data_dest,
		    data_dest.su_len) == 0)
			break;
		conerrno = errno;
		(void) fclose(file);
		data = -1;
		if (conerrno == EADDRINUSE) {
			sleep(swaitint);
			retry += swaitint;
		} else {
			break;
		}
	} while (retry <= swaitmax);
	if (conerrno != 0) {
		reply(425, "Can't build data connection: %s.",
			   strerror(conerrno));
		return (NULL);
	}
	reply(150, "Opening %s mode data connection for '%s'%s.",
	     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
	return (file);
}