#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ err; char* buf; int buflen; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char*) ; 
 scalar_t__ FTP_FILE_ACTION_OK ; 
 int FTP_OK ; 
 int FTP_PROTOCOL_ERROR ; 
 scalar_t__ FTP_WORKING_DIRECTORY ; 

__attribute__((used)) static int
ftp_pwd(conn_t *conn, char *pwd, size_t pwdlen)
{
	char *src, *dst, *end;
	int q;

	if (conn->err != FTP_WORKING_DIRECTORY &&
	    conn->err != FTP_FILE_ACTION_OK)
		return (FTP_PROTOCOL_ERROR);
	end = conn->buf + conn->buflen;
	src = conn->buf + 4;
	if (src >= end || *src++ != '"')
		return (FTP_PROTOCOL_ERROR);
	for (q = 0, dst = pwd; src < end && pwdlen--; ++src) {
		if (!q && *src == '"')
			q = 1;
		else if (q && *src != '"')
			break;
		else if (q)
			*dst++ = '"', q = 0;
		else
			*dst++ = *src;
	}
	if (!pwdlen)
		return (FTP_PROTOCOL_ERROR);
	*dst = '\0';
#if 0
	DEBUGF("pwd: [%s]\n", pwd);
#endif
	return (FTP_OK);
}