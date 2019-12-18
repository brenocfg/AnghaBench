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
struct url {int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 int CHECK_FLAG (char) ; 
 int FTP_LOGGED_IN ; 
 int FTP_SERVICE_READY ; 
 int /*<<< orphan*/  fetch_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fetch_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ftp_authenticate (int /*<<< orphan*/ *,struct url*,struct url*) ; 
 int ftp_chkerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_seterr (int) ; 

__attribute__((used)) static conn_t *
ftp_connect(struct url *url, struct url *purl, const char *flags)
{
	conn_t *conn;
	int e, direct, verbose;
#ifdef INET6
	int af = AF_UNSPEC;
#else
	int af = AF_INET;
#endif

	direct = CHECK_FLAG('d');
	verbose = CHECK_FLAG('v');
	if (CHECK_FLAG('4'))
		af = AF_INET;
	else if (CHECK_FLAG('6'))
		af = AF_INET6;

	if (direct)
		purl = NULL;

	/* check for proxy */
	if (purl) {
		/* XXX proxy authentication! */
		conn = fetch_connect(purl->host, purl->port, af, verbose);
	} else {
		/* no proxy, go straight to target */
		conn = fetch_connect(url->host, url->port, af, verbose);
		purl = NULL;
	}

	/* check connection */
	if (conn == NULL)
		/* fetch_connect() has already set an error code */
		return (NULL);

	/* expect welcome message */
	if ((e = ftp_chkerr(conn)) != FTP_SERVICE_READY)
		goto fouch;

	/* authenticate */
	if ((e = ftp_authenticate(conn, url, purl)) != FTP_LOGGED_IN)
		goto fouch;

	/* TODO: Request extended features supported, if any (RFC 3659). */

	/* done */
	return (conn);

fouch:
	if (e != -1)
		ftp_seterr(e);
	fetch_close(conn);
	return (NULL);
}