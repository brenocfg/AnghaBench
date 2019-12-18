#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct url_stat {int dummy; } ;
struct url {char const* scheme; int /*<<< orphan*/  offset; int /*<<< orphan*/  doc; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ conn_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FETCH_PROTO ; 
 scalar_t__ FETCH_UNAVAIL ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 char* SCHEME_HTTP ; 
 char* SCHEME_HTTPS ; 
 int /*<<< orphan*/  fetchFreeURL (struct url*) ; 
 scalar_t__ fetchLastErrCode ; 
 TYPE_1__* ftp_cached_connect (struct url*,struct url*,char const*) ; 
 int ftp_cwd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftp_disconnect (TYPE_1__*) ; 
 int ftp_stat (TYPE_1__*,int /*<<< orphan*/ ,struct url_stat*) ; 
 int /*<<< orphan*/ * ftp_transfer (TYPE_1__*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * http_request (struct url*,char*,struct url_stat*,struct url*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

FILE *
ftp_request(struct url *url, const char *op, struct url_stat *us,
    struct url *purl, const char *flags)
{
	conn_t *conn;
	int oflag;

	/* check if we should use HTTP instead */
	if (purl && (strcmp(purl->scheme, SCHEME_HTTP) == 0 ||
	    strcmp(purl->scheme, SCHEME_HTTPS) == 0)) {
		if (strcmp(op, "STAT") == 0)
			return (http_request(url, "HEAD", us, purl, flags));
		else if (strcmp(op, "RETR") == 0)
			return (http_request(url, "GET", us, purl, flags));
		/*
		 * Our HTTP code doesn't support PUT requests yet, so try
		 * a direct connection.
		 */
	}

	/* connect to server */
	conn = ftp_cached_connect(url, purl, flags);
	if (purl)
		fetchFreeURL(purl);
	if (conn == NULL)
		return (NULL);

	/* change directory */
	if (ftp_cwd(conn, url->doc) == -1)
		goto errsock;

	/* stat file */
	if (us && ftp_stat(conn, url->doc, us) == -1
	    && fetchLastErrCode != FETCH_PROTO
	    && fetchLastErrCode != FETCH_UNAVAIL)
		goto errsock;

	/* just a stat */
	if (strcmp(op, "STAT") == 0) {
		--conn->ref;
		ftp_disconnect(conn);
		return (FILE *)1; /* bogus return value */
	}
	if (strcmp(op, "STOR") == 0 || strcmp(op, "APPE") == 0)
		oflag = O_WRONLY;
	else
		oflag = O_RDONLY;

	/* initiate the transfer */
	return (ftp_transfer(conn, op, url->doc, oflag, url->offset, flags));

errsock:
	ftp_disconnect(conn);
	return (NULL);
}