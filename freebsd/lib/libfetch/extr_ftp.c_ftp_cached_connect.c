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
struct url {int /*<<< orphan*/  scheme; scalar_t__ port; } ;
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int FTP_OK ; 
 int FTP_SYNTAX_ERROR ; 
 int /*<<< orphan*/ * cached_connection ; 
 int /*<<< orphan*/  cached_host ; 
 scalar_t__ fetch_default_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fetch_ref (int /*<<< orphan*/ *) ; 
 int ftp_cmd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ftp_connect (struct url*,struct url*,char const*) ; 
 int /*<<< orphan*/  ftp_disconnect (int /*<<< orphan*/ *) ; 
 scalar_t__ ftp_isconnected (struct url*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct url*,int) ; 

__attribute__((used)) static conn_t *
ftp_cached_connect(struct url *url, struct url *purl, const char *flags)
{
	conn_t *conn;
	int e;

	/* set default port */
	if (!url->port)
		url->port = fetch_default_port(url->scheme);

	/* try to use previously cached connection */
	if (ftp_isconnected(url)) {
		e = ftp_cmd(cached_connection, "NOOP");
		if (e == FTP_OK || e == FTP_SYNTAX_ERROR)
			return (fetch_ref(cached_connection));
	}

	/* connect to server */
	if ((conn = ftp_connect(url, purl, flags)) == NULL)
		return (NULL);
	if (cached_connection)
		ftp_disconnect(cached_connection);
	cached_connection = fetch_ref(conn);
	memcpy(&cached_host, url, sizeof(*url));
	return (conn);
}