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
struct httpread {char* hdr; int hdr_type; int version; int reply_code; char* uri; scalar_t__ chunked; scalar_t__ got_content_length; int /*<<< orphan*/  max_bytes; } ;

/* Variables and functions */
#define  HTTPREAD_HDR_TYPE_CONNECT 140 
#define  HTTPREAD_HDR_TYPE_DELETE 139 
#define  HTTPREAD_HDR_TYPE_GET 138 
#define  HTTPREAD_HDR_TYPE_HEAD 137 
#define  HTTPREAD_HDR_TYPE_M_POST 136 
#define  HTTPREAD_HDR_TYPE_M_SEARCH 135 
#define  HTTPREAD_HDR_TYPE_NOTIFY 134 
#define  HTTPREAD_HDR_TYPE_POST 133 
#define  HTTPREAD_HDR_TYPE_PUT 132 
#define  HTTPREAD_HDR_TYPE_REPLY 131 
#define  HTTPREAD_HDR_TYPE_SUBSCRIBE 130 
#define  HTTPREAD_HDR_TYPE_TRACE 129 
 int HTTPREAD_HDR_TYPE_UNKNOWN ; 
#define  HTTPREAD_HDR_TYPE_UNSUBSCRIBE 128 
 int atol (char*) ; 
 int /*<<< orphan*/  hex2byte (char*) ; 
 scalar_t__ httpread_hdr_option_analyze (struct httpread*,char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isgraph (char) ; 
 scalar_t__ isxdigit (char) ; 
 char* os_malloc (int) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ word_eq (char*,char*) ; 

__attribute__((used)) static int httpread_hdr_analyze(struct httpread *h)
{
	char *hbp = h->hdr;      /* pointer into h->hdr */
	int standard_first_line = 1;

	/* First line is special */
	h->hdr_type = HTTPREAD_HDR_TYPE_UNKNOWN;
	if (!isgraph(*hbp))
		goto bad;
	if (os_strncmp(hbp, "HTTP/", 5) == 0) {
		h->hdr_type = HTTPREAD_HDR_TYPE_REPLY;
		standard_first_line = 0;
		hbp += 5;
		if (hbp[0] == '1' && hbp[1] == '.' &&
		    isdigit(hbp[2]) && hbp[2] != '0')
			h->version = 1;
		while (isgraph(*hbp))
			hbp++;
		while (*hbp == ' ' || *hbp == '\t')
			hbp++;
		if (!isdigit(*hbp))
			goto bad;
		h->reply_code = atol(hbp);
	} else if (word_eq(hbp, "GET"))
		h->hdr_type = HTTPREAD_HDR_TYPE_GET;
	else if (word_eq(hbp, "HEAD"))
		h->hdr_type = HTTPREAD_HDR_TYPE_HEAD;
	else if (word_eq(hbp, "POST"))
		h->hdr_type = HTTPREAD_HDR_TYPE_POST;
	else if (word_eq(hbp, "PUT"))
		h->hdr_type = HTTPREAD_HDR_TYPE_PUT;
	else if (word_eq(hbp, "DELETE"))
		h->hdr_type = HTTPREAD_HDR_TYPE_DELETE;
	else if (word_eq(hbp, "TRACE"))
		h->hdr_type = HTTPREAD_HDR_TYPE_TRACE;
	else if (word_eq(hbp, "CONNECT"))
		h->hdr_type = HTTPREAD_HDR_TYPE_CONNECT;
	else if (word_eq(hbp, "NOTIFY"))
		h->hdr_type = HTTPREAD_HDR_TYPE_NOTIFY;
	else if (word_eq(hbp, "M-SEARCH"))
		h->hdr_type = HTTPREAD_HDR_TYPE_M_SEARCH;
	else if (word_eq(hbp, "M-POST"))
		h->hdr_type = HTTPREAD_HDR_TYPE_M_POST;
	else if (word_eq(hbp, "SUBSCRIBE"))
		h->hdr_type = HTTPREAD_HDR_TYPE_SUBSCRIBE;
	else if (word_eq(hbp, "UNSUBSCRIBE"))
		h->hdr_type = HTTPREAD_HDR_TYPE_UNSUBSCRIBE;
	else {
	}

	if (standard_first_line) {
		char *rawuri;
		char *uri;
		/* skip type */
		while (isgraph(*hbp))
			hbp++;
		while (*hbp == ' ' || *hbp == '\t')
			hbp++;
		/* parse uri.
		 * Find length, allocate memory for translated
		 * copy, then translate by changing %<hex><hex>
		 * into represented value.
		 */
		rawuri = hbp;
		while (isgraph(*hbp))
			hbp++;
		h->uri = os_malloc((hbp - rawuri) + 1);
		if (h->uri == NULL)
			goto bad;
		uri = h->uri;
		while (rawuri < hbp) {
			int c = *rawuri;
			if (c == '%' &&
			    isxdigit(rawuri[1]) && isxdigit(rawuri[2])) {
				*uri++ = hex2byte(rawuri + 1);
				rawuri += 3;
			} else {
				*uri++ = c;
				rawuri++;
			}
		}
		*uri = 0;       /* null terminate */
		while (*hbp == ' ' || *hbp == '\t')
			hbp++;
		/* get version */
		if (0 == strncmp(hbp, "HTTP/", 5)) {
			hbp += 5;
			if (hbp[0] == '1' && hbp[1] == '.' &&
			    isdigit(hbp[2]) && hbp[2] != '0')
				h->version = 1;
		}
	}
	/* skip rest of line */
	while (*hbp)
		if (*hbp++ == '\n')
			break;

	/* Remainder of lines are options, in any order;
	 * or empty line to terminate
	 */
	for (;;) {
		/* Empty line to terminate */
		if (hbp[0] == '\n' ||
		    (hbp[0] == '\r' && hbp[1] == '\n'))
			break;
		if (!isgraph(*hbp))
			goto bad;
		if (httpread_hdr_option_analyze(h, hbp))
			goto bad;
		/* skip line */
		while (*hbp)
			if (*hbp++ == '\n')
				break;
	}

	/* chunked overrides content-length always */
	if (h->chunked)
		h->got_content_length = 0;

	/* For some types, we should not try to read a body
	 * This is in addition to the application determining
	 * that we should not read a body.
	 */
	switch (h->hdr_type) {
	case HTTPREAD_HDR_TYPE_REPLY:
		/* Some codes can have a body and some not.
		 * For now, just assume that any other than 200
		 * do not...
		 */
		if (h->reply_code != 200)
			h->max_bytes = 0;
		break;
	case HTTPREAD_HDR_TYPE_GET:
	case HTTPREAD_HDR_TYPE_HEAD:
		/* in practice it appears that it is assumed
		 * that GETs have a body length of 0... ?
		 */
		if (h->chunked == 0 && h->got_content_length == 0)
			h->max_bytes = 0;
		break;
	case HTTPREAD_HDR_TYPE_POST:
	case HTTPREAD_HDR_TYPE_PUT:
	case HTTPREAD_HDR_TYPE_DELETE:
	case HTTPREAD_HDR_TYPE_TRACE:
	case HTTPREAD_HDR_TYPE_CONNECT:
	case HTTPREAD_HDR_TYPE_NOTIFY:
	case HTTPREAD_HDR_TYPE_M_SEARCH:
	case HTTPREAD_HDR_TYPE_M_POST:
	case HTTPREAD_HDR_TYPE_SUBSCRIBE:
	case HTTPREAD_HDR_TYPE_UNSUBSCRIBE:
	default:
		break;
	}

	return 0;

bad:
	/* Error */
	return -1;
}