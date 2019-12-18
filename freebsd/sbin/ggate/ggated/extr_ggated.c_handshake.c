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
typedef  int /*<<< orphan*/  ver ;
struct sockaddr {int dummy; } ;
struct ggd_export {int dummy; } ;
struct ggd_connection {scalar_t__ c_mediasize; int /*<<< orphan*/  c_sectorsize; int /*<<< orphan*/  c_diskfd; scalar_t__ c_token; } ;
struct g_gate_version {scalar_t__ gv_version; scalar_t__ gs_mediasize; scalar_t__ gs_error; int /*<<< orphan*/  gs_sectorsize; scalar_t__ gv_error; int /*<<< orphan*/  gv_magic; } ;
struct g_gate_sinit {scalar_t__ gv_version; scalar_t__ gs_mediasize; scalar_t__ gs_error; int /*<<< orphan*/  gs_sectorsize; scalar_t__ gv_error; int /*<<< orphan*/  gv_magic; } ;
struct g_gate_cinit {scalar_t__ gv_version; scalar_t__ gs_mediasize; scalar_t__ gs_error; int /*<<< orphan*/  gs_sectorsize; scalar_t__ gv_error; int /*<<< orphan*/  gv_magic; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sinit ;
typedef  int /*<<< orphan*/  cinit ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GGATE_MAGIC ; 
 scalar_t__ GGATE_VERSION ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int connection_add (struct ggd_connection*,struct g_gate_version*,struct sockaddr*,int) ; 
 struct ggd_connection* connection_find (struct g_gate_version*) ; 
 int /*<<< orphan*/  connection_launch (struct ggd_connection*) ; 
 struct ggd_connection* connection_new (struct g_gate_version*,struct sockaddr*,int) ; 
 scalar_t__ connection_ready (struct ggd_connection*) ; 
 int /*<<< orphan*/  connection_remove (struct ggd_connection*) ; 
 int /*<<< orphan*/  errno ; 
 struct ggd_export* exports_find (struct sockaddr*,struct g_gate_version*,struct ggd_connection*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ g_gate_mediasize (int /*<<< orphan*/ ) ; 
 int g_gate_recv (int,struct g_gate_version*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_sectorsize (int /*<<< orphan*/ ) ; 
 int g_gate_send (int,struct g_gate_version*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_swap2h_cinit (struct g_gate_version*) ; 
 int /*<<< orphan*/  g_gate_swap2h_sinit (struct g_gate_version*) ; 
 int /*<<< orphan*/  g_gate_swap2h_version (struct g_gate_version*) ; 
 int /*<<< orphan*/  g_gate_swap2n_sinit (struct g_gate_version*) ; 
 int /*<<< orphan*/  g_gate_swap2n_version (struct g_gate_version*) ; 
 int /*<<< orphan*/  log_connection (struct sockaddr*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendfail (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
handshake(struct sockaddr *from, int sfd)
{
	struct g_gate_version ver;
	struct g_gate_cinit cinit;
	struct g_gate_sinit sinit;
	struct ggd_connection *conn;
	struct ggd_export *ex;
	ssize_t data;

	log_connection(from);
	/*
	 * Phase 1: Version verification.
	 */
	g_gate_log(LOG_DEBUG, "Receiving version packet.");
	data = g_gate_recv(sfd, &ver, sizeof(ver), MSG_WAITALL);
	g_gate_swap2h_version(&ver);
	if (data != sizeof(ver)) {
		g_gate_log(LOG_WARNING, "Malformed version packet.");
		return (0);
	}
	g_gate_log(LOG_DEBUG, "Version packet received.");
	if (memcmp(ver.gv_magic, GGATE_MAGIC, strlen(GGATE_MAGIC)) != 0) {
		g_gate_log(LOG_WARNING, "Invalid magic field.");
		return (0);
	}
	if (ver.gv_version != GGATE_VERSION) {
		g_gate_log(LOG_WARNING, "Version %u is not supported.",
		    ver.gv_version);
		return (0);
	}
	ver.gv_error = 0;
	g_gate_swap2n_version(&ver);
	data = g_gate_send(sfd, &ver, sizeof(ver), 0);
	g_gate_swap2h_version(&ver);
	if (data == -1) {
		sendfail(sfd, errno, "Error while sending version packet: %s.",
		    strerror(errno));
		return (0);
	}

	/*
	 * Phase 2: Request verification.
	 */
	g_gate_log(LOG_DEBUG, "Receiving initial packet.");
	data = g_gate_recv(sfd, &cinit, sizeof(cinit), MSG_WAITALL);
	g_gate_swap2h_cinit(&cinit);
	if (data != sizeof(cinit)) {
		g_gate_log(LOG_WARNING, "Malformed initial packet.");
		return (0);
	}
	g_gate_log(LOG_DEBUG, "Initial packet received.");
	conn = connection_find(&cinit);
	if (conn != NULL) {
		/*
		 * Connection should already exists.
		 */
		g_gate_log(LOG_DEBUG, "Found existing connection (token=%lu).",
		    (unsigned long)conn->c_token);
		if (connection_add(conn, &cinit, from, sfd) == -1) {
			connection_remove(conn);
			return (0);
		}
	} else {
		/*
		 * New connection, allocate space.
		 */
		conn = connection_new(&cinit, from, sfd);
		if (conn == NULL) {
			sendfail(sfd, ENOMEM,
			    "Cannot allocate new connection.");
			return (0);
		}
		g_gate_log(LOG_DEBUG, "New connection created (token=%lu).",
		    (unsigned long)conn->c_token);
	}

	ex = exports_find(from, &cinit, conn);
	if (ex == NULL) {
		sendfail(sfd, errno, NULL);
		connection_remove(conn);
		return (0);
	}
	if (conn->c_mediasize == 0) {
		conn->c_mediasize = g_gate_mediasize(conn->c_diskfd);
		conn->c_sectorsize = g_gate_sectorsize(conn->c_diskfd);
	}
	sinit.gs_mediasize = conn->c_mediasize;
	sinit.gs_sectorsize = conn->c_sectorsize;
	sinit.gs_error = 0;

	g_gate_log(LOG_DEBUG, "Sending initial packet.");

	g_gate_swap2n_sinit(&sinit);
	data = g_gate_send(sfd, &sinit, sizeof(sinit), 0);
	g_gate_swap2h_sinit(&sinit);
	if (data == -1) {
		sendfail(sfd, errno, "Error while sending initial packet: %s.",
		    strerror(errno));
		return (0);
	}

	if (connection_ready(conn)) {
		connection_launch(conn);
		connection_remove(conn);
	}
	return (1);
}