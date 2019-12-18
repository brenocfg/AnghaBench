#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct url {int /*<<< orphan*/  scheme; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  http_headerbuf_t ;
typedef  scalar_t__ hdr_t ;
struct TYPE_10__ {int /*<<< orphan*/  sd; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 int CHECK_FLAG (char) ; 
 int EAUTH ; 
 scalar_t__ HTTP_OK ; 
 int /*<<< orphan*/  HTTP_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SCHEME_HTTPS ; 
 int /*<<< orphan*/  TCP_NOPUSH ; 
 int /*<<< orphan*/  clean_http_headerbuf (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fetch_close (TYPE_1__*) ; 
 TYPE_1__* fetch_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ fetch_getln (TYPE_1__*) ; 
 int fetch_ssl (TYPE_1__*,struct url*,int) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 scalar_t__ hdr_end ; 
#define  hdr_error 129 
#define  hdr_syserror 128 
 int /*<<< orphan*/  http_cmd (TYPE_1__*,char*,...) ; 
 scalar_t__ http_get_reply (TYPE_1__*) ; 
 scalar_t__ http_next_header (TYPE_1__*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  http_seterr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_http_headerbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static conn_t *
http_connect(struct url *URL, struct url *purl, const char *flags)
{
	struct url *curl;
	conn_t *conn;
	hdr_t h;
	http_headerbuf_t headerbuf;
	const char *p;
	int verbose;
	int af, val;
	int serrno;

#ifdef INET6
	af = AF_UNSPEC;
#else
	af = AF_INET;
#endif

	verbose = CHECK_FLAG('v');
	if (CHECK_FLAG('4'))
		af = AF_INET;
#ifdef INET6
	else if (CHECK_FLAG('6'))
		af = AF_INET6;
#endif

	curl = (purl != NULL) ? purl : URL;

	if ((conn = fetch_connect(curl->host, curl->port, af, verbose)) == NULL)
		/* fetch_connect() has already set an error code */
		return (NULL);
	init_http_headerbuf(&headerbuf);
	if (strcmp(URL->scheme, SCHEME_HTTPS) == 0 && purl) {
		http_cmd(conn, "CONNECT %s:%d HTTP/1.1",
		    URL->host, URL->port);
		http_cmd(conn, "Host: %s:%d",
		    URL->host, URL->port);
		http_cmd(conn, "");
		if (http_get_reply(conn) != HTTP_OK) {
			http_seterr(conn->err);
			goto ouch;
		}
		/* Read and discard the rest of the proxy response */
		if (fetch_getln(conn) < 0) {
			fetch_syserr();
			goto ouch;
		}
		do {
			switch ((h = http_next_header(conn, &headerbuf, &p))) {
			case hdr_syserror:
				fetch_syserr();
				goto ouch;
			case hdr_error:
				http_seterr(HTTP_PROTOCOL_ERROR);
				goto ouch;
			default:
				/* ignore */ ;
			}
		} while (h > hdr_end);
	}
	if (strcmp(URL->scheme, SCHEME_HTTPS) == 0 &&
	    fetch_ssl(conn, URL, verbose) == -1) {
		/* grrr */
		errno = EAUTH;
		fetch_syserr();
		goto ouch;
	}

	val = 1;
	setsockopt(conn->sd, IPPROTO_TCP, TCP_NOPUSH, &val, sizeof(val));

	clean_http_headerbuf(&headerbuf);
	return (conn);
ouch:
	serrno = errno;
	clean_http_headerbuf(&headerbuf);
	fetch_close(conn);
	errno = serrno;
	return (NULL);
}