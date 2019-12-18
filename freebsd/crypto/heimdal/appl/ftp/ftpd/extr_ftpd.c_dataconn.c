#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sizebuf ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  from_ss ;
typedef  int /*<<< orphan*/  data_addr ;
struct TYPE_11__ {int sa_family; } ;
struct TYPE_10__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_9__ {int sa_family; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  IPTOS_THROUGHPUT ; 
 int PF_UNSPEC ; 
 scalar_t__ TYPE_A ; 
 int accept_with_timeout (int,struct sockaddr*,int*,struct timeval*) ; 
 scalar_t__ byte_count ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ctrl_addr ; 
 int data ; 
 TYPE_1__* data_dest ; 
 TYPE_2__* data_source ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 scalar_t__ file_size ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getdatasock (char const*,int) ; 
 TYPE_1__* his_addr ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int pdata ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 
 int /*<<< orphan*/  socket_get_address (TYPE_2__*) ; 
 char const* socket_get_port (TYPE_2__*) ; 
 int /*<<< orphan*/  socket_set_tos (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_sockaddr_size (TYPE_1__*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ swaitint ; 
 int swaitmax ; 
 scalar_t__ type ; 
 int usedefault ; 

__attribute__((used)) static FILE *
dataconn(const char *name, off_t size, const char *mode)
{
	char sizebuf[32];
	FILE *file;
	int domain, retry = 0;

	file_size = size;
	byte_count = 0;
	if (size >= 0)
	    snprintf(sizebuf, sizeof(sizebuf), " (%ld bytes)", (long)size);
	else
	    *sizebuf = '\0';
	if (pdata >= 0) {
		struct sockaddr_storage from_ss;
		struct sockaddr *from = (struct sockaddr *)&from_ss;
		struct timeval timeout;
		int s;
		socklen_t fromlen = sizeof(from_ss);

		timeout.tv_sec = 15;
		timeout.tv_usec = 0;
		s = accept_with_timeout(pdata, from, &fromlen, &timeout);
		if (s < 0) {
			reply(425, "Can't open data connection.");
			close(pdata);
			pdata = -1;
			return (NULL);
		}
		close(pdata);
		pdata = s;
#if defined(IPTOS_THROUGHPUT)
		if (from->sa_family == AF_INET)
		    socket_set_tos(s, IPTOS_THROUGHPUT);
#endif
		reply(150, "Opening %s mode data connection for '%s'%s.",
		     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
		return (fdopen(pdata, mode));
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
	/*
	 * Default to using the same socket type as the ctrl address,
	 * unless we know the type of the data address.
	 */
	domain = data_dest->sa_family;
	if (domain == PF_UNSPEC)
	    domain = ctrl_addr->sa_family;

	file = getdatasock(mode, domain);
	if (file == NULL) {
		char data_addr[256];

		if (inet_ntop (data_source->sa_family,
			       socket_get_address(data_source),
			       data_addr, sizeof(data_addr)) == NULL)
			strlcpy (data_addr, "unknown address",
					 sizeof(data_addr));

		reply(425, "Can't create data socket (%s,%d): %s.",
		      data_addr,
		      socket_get_port (data_source),
		      strerror(errno));
		return (NULL);
	}
	data = fileno(file);
	while (connect(data, data_dest,
		       socket_sockaddr_size(data_dest)) < 0) {
		if (errno == EADDRINUSE && retry < swaitmax) {
			sleep(swaitint);
			retry += swaitint;
			continue;
		}
		perror_reply(425, "Can't build data connection");
		fclose(file);
		data = -1;
		return (NULL);
	}
	reply(150, "Opening %s mode data connection for '%s'%s.",
	     type == TYPE_A ? "ASCII" : "BINARY", name, sizebuf);
	return (file);
}