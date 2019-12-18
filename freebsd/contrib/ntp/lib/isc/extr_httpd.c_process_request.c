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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {int recvlen; char* recvbuf; char* url; char* protocol; int flags; scalar_t__* querystring; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ isc_httpd_t ;

/* Variables and functions */
 scalar_t__ BUFLENOK (char*) ; 
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  EXIT (char*) ; 
 int HTTPD_CLOSE ; 
 int HTTPD_FOUNDHOST ; 
 int /*<<< orphan*/  ISC_HTTPD_METHODGET ; 
 int /*<<< orphan*/  ISC_HTTPD_METHODPOST ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ LENGTHOK (char*) ; 
 scalar_t__* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static isc_result_t
process_request(isc_httpd_t *httpd, int length)
{
	char *s;
	char *p;
	int delim;

	ENTER("request");

	httpd->recvlen += length;

	httpd->recvbuf[httpd->recvlen] = 0;

	/*
	 * If we don't find a blank line in our buffer, return that we need
	 * more data.
	 */
	s = strstr(httpd->recvbuf, "\r\n\r\n");
	delim = 1;
	if (s == NULL) {
		s = strstr(httpd->recvbuf, "\n\n");
		delim = 2;
	}
	if (s == NULL)
		return (ISC_R_NOTFOUND);

	/*
	 * Determine if this is a POST or GET method.  Any other values will
	 * cause an error to be returned.
	 */
	if (strncmp(httpd->recvbuf, "GET ", 4) == 0) {
		httpd->method = ISC_HTTPD_METHODGET;
		p = httpd->recvbuf + 4;
	} else if (strncmp(httpd->recvbuf, "POST ", 5) == 0) {
		httpd->method = ISC_HTTPD_METHODPOST;
		p = httpd->recvbuf + 5;
	} else {
		return (ISC_R_RANGE);
	}

	/*
	 * From now on, p is the start of our buffer.
	 */

	/*
	 * Extract the URL.
	 */
	s = p;
	while (LENGTHOK(s) && BUFLENOK(s) &&
	       (*s != '\n' && *s != '\r' && *s != '\0' && *s != ' '))
		s++;
	if (!LENGTHOK(s))
		return (ISC_R_NOTFOUND);
	if (!BUFLENOK(s))
		return (ISC_R_NOMEMORY);
	*s = 0;

	/*
	 * Make the URL relative.
	 */
	if ((strncmp(p, "http:/", 6) == 0)
	    || (strncmp(p, "https:/", 7) == 0)) {
		/* Skip first / */
		while (*p != '/' && *p != 0)
			p++;
		if (*p == 0)
			return (ISC_R_RANGE);
		p++;
		/* Skip second / */
		while (*p != '/' && *p != 0)
			p++;
		if (*p == 0)
			return (ISC_R_RANGE);
		p++;
		/* Find third / */
		while (*p != '/' && *p != 0)
			p++;
		if (*p == 0) {
			p--;
			*p = '/';
		}
	}

	httpd->url = p;
	p = s + delim;
	s = p;

	/*
	 * Now, see if there is a ? mark in the URL.  If so, this is
	 * part of the query string, and we will split it from the URL.
	 */
	httpd->querystring = strchr(httpd->url, '?');
	if (httpd->querystring != NULL) {
		*(httpd->querystring) = 0;
		httpd->querystring++;
	}

	/*
	 * Extract the HTTP/1.X protocol.  We will bounce on anything but
	 * HTTP/1.1 for now.
	 */
	while (LENGTHOK(s) && BUFLENOK(s) &&
	       (*s != '\n' && *s != '\r' && *s != '\0'))
		s++;
	if (!LENGTHOK(s))
		return (ISC_R_NOTFOUND);
	if (!BUFLENOK(s))
		return (ISC_R_NOMEMORY);
	*s = 0;
	if ((strncmp(p, "HTTP/1.0", 8) != 0)
	    && (strncmp(p, "HTTP/1.1", 8) != 0))
		return (ISC_R_RANGE);
	httpd->protocol = p;
	p = s + 1;
	s = p;

	if (strstr(s, "Connection: close") != NULL)
		httpd->flags |= HTTPD_CLOSE;

	if (strstr(s, "Host: ") != NULL)
		httpd->flags |= HTTPD_FOUNDHOST;

	/*
	 * Standards compliance hooks here.
	 */
	if (strcmp(httpd->protocol, "HTTP/1.1") == 0
	    && ((httpd->flags & HTTPD_FOUNDHOST) == 0))
		return (ISC_R_RANGE);

	EXIT("request");

	return (ISC_R_SUCCESS);
}