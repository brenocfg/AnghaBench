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
struct url {char* user; char* pwd; int /*<<< orphan*/  port; int /*<<< orphan*/  host; int /*<<< orphan*/  scheme; } ;
typedef  int /*<<< orphan*/  pbuf ;
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char const*) ; 
 char* FTP_ANONYMOUS_USER ; 
 int FTP_NEED_PASSWORD ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  fetch_default_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_netrc_auth (struct url*) ; 
 int ftp_cmd (int /*<<< orphan*/ *,char*,char const*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 char* getlogin () ; 
 int snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
ftp_authenticate(conn_t *conn, struct url *url, struct url *purl)
{
	const char *user, *pwd, *logname;
	char pbuf[MAXHOSTNAMELEN + MAXLOGNAME + 1];
	int e, len;

	/* XXX FTP_AUTH, and maybe .netrc */

	/* send user name and password */
	if (url->user[0] == '\0')
		fetch_netrc_auth(url);
	user = url->user;
	if (*user == '\0')
		if ((user = getenv("FTP_LOGIN")) != NULL)
			DEBUGF("FTP_LOGIN=%s\n", user);
	if (user == NULL || *user == '\0')
		user = FTP_ANONYMOUS_USER;
	if (purl && url->port == fetch_default_port(url->scheme))
		e = ftp_cmd(conn, "USER %s@%s", user, url->host);
	else if (purl)
		e = ftp_cmd(conn, "USER %s@%s@%d", user, url->host, url->port);
	else
		e = ftp_cmd(conn, "USER %s", user);

	/* did the server request a password? */
	if (e == FTP_NEED_PASSWORD) {
		pwd = url->pwd;
		if (*pwd == '\0')
			if ((pwd = getenv("FTP_PASSWORD")) != NULL)
				DEBUGF("FTP_PASSWORD=%s\n", pwd);
		if (pwd == NULL || *pwd == '\0') {
			if ((logname = getlogin()) == NULL)
				logname = FTP_ANONYMOUS_USER;
			if ((len = snprintf(pbuf, MAXLOGNAME + 1, "%s@", logname)) < 0)
				len = 0;
			else if (len > MAXLOGNAME)
				len = MAXLOGNAME;
			gethostname(pbuf + len, sizeof(pbuf) - len);
			pwd = pbuf;
		}
		e = ftp_cmd(conn, "PASS %s", pwd);
	}

	return (e);
}