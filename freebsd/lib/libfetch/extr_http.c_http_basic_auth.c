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
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char const*) ; 
 int asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* http_base64 (char*) ; 
 int http_cmd (int /*<<< orphan*/ *,char*,char const*,char*) ; 

__attribute__((used)) static int
http_basic_auth(conn_t *conn, const char *hdr, const char *usr, const char *pwd)
{
	char *upw, *auth;
	int r;

	DEBUGF("basic: usr: [%s]\n", usr);
	DEBUGF("basic: pwd: [%s]\n", pwd);
	if (asprintf(&upw, "%s:%s", usr, pwd) == -1)
		return (-1);
	auth = http_base64(upw);
	free(upw);
	if (auth == NULL)
		return (-1);
	r = http_cmd(conn, "%s: Basic %s", hdr, auth);
	free(auth);
	return (r);
}