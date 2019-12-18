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
typedef  int /*<<< orphan*/  ver ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ gv_error; int gc_flags; int gc_nconn; scalar_t__ gs_error; scalar_t__ gs_sectorsize; int /*<<< orphan*/  gs_mediasize; int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_path; int /*<<< orphan*/  gv_version; int /*<<< orphan*/  gv_magic; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct g_gate_version {scalar_t__ gv_error; int gc_flags; int gc_nconn; scalar_t__ gs_error; scalar_t__ gs_sectorsize; int /*<<< orphan*/  gs_mediasize; int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_path; int /*<<< orphan*/  gv_version; int /*<<< orphan*/  gv_magic; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct g_gate_sinit {scalar_t__ gv_error; int gc_flags; int gc_nconn; scalar_t__ gs_error; scalar_t__ gs_sectorsize; int /*<<< orphan*/  gs_mediasize; int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_path; int /*<<< orphan*/  gv_version; int /*<<< orphan*/  gv_magic; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct g_gate_cinit {scalar_t__ gv_error; int gc_flags; int gc_nconn; scalar_t__ gs_error; scalar_t__ gs_sectorsize; int /*<<< orphan*/  gs_mediasize; int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_path; int /*<<< orphan*/  gv_version; int /*<<< orphan*/  gv_magic; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  sinit ;
typedef  int /*<<< orphan*/  serv ;
typedef  int /*<<< orphan*/  cinit ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  GGATE_MAGIC ; 
 int /*<<< orphan*/  GGATE_VERSION ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int flags ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,...) ; 
 int g_gate_recv (int,struct sockaddr_in*,int,int /*<<< orphan*/ ) ; 
 int g_gate_send (int,struct sockaddr_in*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_socket_settings (int) ; 
 scalar_t__ g_gate_str2ip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_swap2h_cinit (struct sockaddr_in*) ; 
 int /*<<< orphan*/  g_gate_swap2h_sinit (struct sockaddr_in*) ; 
 int /*<<< orphan*/  g_gate_swap2n_cinit (struct sockaddr_in*) ; 
 int /*<<< orphan*/  g_gate_swap2n_version (struct sockaddr_in*) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mediasize ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  port ; 
 scalar_t__ sectorsize ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token ; 

__attribute__((used)) static int
handshake(int dir)
{
	struct g_gate_version ver;
	struct g_gate_cinit cinit;
	struct g_gate_sinit sinit;
	struct sockaddr_in serv;
	int sfd;

	/*
	 * Do the network stuff.
	 */
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = g_gate_str2ip(host);
	if (serv.sin_addr.s_addr == INADDR_NONE) {
		g_gate_log(LOG_DEBUG, "Invalid IP/host name: %s.", host);
		return (-1);
	}
	serv.sin_port = htons(port);
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) {
		g_gate_log(LOG_DEBUG, "Cannot open socket: %s.",
		    strerror(errno));
		return (-1);
	}

	g_gate_socket_settings(sfd);

	if (connect(sfd, (struct sockaddr *)&serv, sizeof(serv)) == -1) {
		g_gate_log(LOG_DEBUG, "Cannot connect to server: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}

	g_gate_log(LOG_INFO, "Connected to the server: %s:%d.", host, port);

	/*
	 * Create and send version packet.
	 */
	g_gate_log(LOG_DEBUG, "Sending version packet.");
	assert(strlen(GGATE_MAGIC) == sizeof(ver.gv_magic));
	bcopy(GGATE_MAGIC, ver.gv_magic, sizeof(ver.gv_magic));
	ver.gv_version = GGATE_VERSION;
	ver.gv_error = 0;
	g_gate_swap2n_version(&ver);
	if (g_gate_send(sfd, &ver, sizeof(ver), MSG_NOSIGNAL) == -1) {
		g_gate_log(LOG_DEBUG, "Error while sending version packet: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}
	bzero(&ver, sizeof(ver));
	if (g_gate_recv(sfd, &ver, sizeof(ver), MSG_WAITALL) == -1) {
		g_gate_log(LOG_DEBUG, "Error while receiving data: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}
	if (ver.gv_error != 0) {
		g_gate_log(LOG_DEBUG, "Version verification problem: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}

	/*
	 * Create and send initial packet.
	 */
	g_gate_log(LOG_DEBUG, "Sending initial packet.");
	if (strlcpy(cinit.gc_path, path, sizeof(cinit.gc_path)) >=
	    sizeof(cinit.gc_path)) {
		g_gate_log(LOG_DEBUG, "Path name too long.");
		close(sfd);
		return (-1);
	}
	cinit.gc_flags = flags | dir;
	cinit.gc_token = token;
	cinit.gc_nconn = 2;
	g_gate_swap2n_cinit(&cinit);
	if (g_gate_send(sfd, &cinit, sizeof(cinit), MSG_NOSIGNAL) == -1) {
	        g_gate_log(LOG_DEBUG, "Error while sending initial packet: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}
	g_gate_swap2h_cinit(&cinit);

	/*
	 * Receiving initial packet from server.
	 */
	g_gate_log(LOG_DEBUG, "Receiving initial packet.");
	if (g_gate_recv(sfd, &sinit, sizeof(sinit), MSG_WAITALL) == -1) {
		g_gate_log(LOG_DEBUG, "Error while receiving data: %s.",
		    strerror(errno));
		close(sfd);
		return (-1);
	}
	g_gate_swap2h_sinit(&sinit);
	if (sinit.gs_error != 0) {
	        g_gate_log(LOG_DEBUG, "Error from server: %s.",
		    strerror(sinit.gs_error));
		close(sfd);
		return (-1);
	}
	g_gate_log(LOG_DEBUG, "Received initial packet.");

	mediasize = sinit.gs_mediasize;
	if (sectorsize == 0)
		sectorsize = sinit.gs_sectorsize;

	return (sfd);
}