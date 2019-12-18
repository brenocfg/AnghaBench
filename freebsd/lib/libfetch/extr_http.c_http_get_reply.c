#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; char err; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int HTTP_PROTOCOL_ERROR ; 
 int fetch_getln (TYPE_1__*) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
http_get_reply(conn_t *conn)
{
	char *p;

	if (fetch_getln(conn) == -1)
		return (-1);
	/*
	 * A valid status line looks like "HTTP/m.n xyz reason" where m
	 * and n are the major and minor protocol version numbers and xyz
	 * is the reply code.
	 * Unfortunately, there are servers out there (NCSA 1.5.1, to name
	 * just one) that do not send a version number, so we can't rely
	 * on finding one, but if we do, insist on it being 1.0 or 1.1.
	 * We don't care about the reason phrase.
	 */
	if (strncmp(conn->buf, "HTTP", 4) != 0)
		return (HTTP_PROTOCOL_ERROR);
	p = conn->buf + 4;
	if (*p == '/') {
		if (p[1] != '1' || p[2] != '.' || (p[3] != '0' && p[3] != '1'))
			return (HTTP_PROTOCOL_ERROR);
		p += 4;
	}
	if (*p != ' ' ||
	    !isdigit((unsigned char)p[1]) ||
	    !isdigit((unsigned char)p[2]) ||
	    !isdigit((unsigned char)p[3]))
		return (HTTP_PROTOCOL_ERROR);

	conn->err = (p[1] - '0') * 100 + (p[2] - '0') * 10 + (p[3] - '0');
	return (conn->err);
}