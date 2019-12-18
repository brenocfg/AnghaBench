#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bufsize; unsigned int buflen; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ http_headerbuf_t ;
typedef  scalar_t__ hdr_t ;
struct TYPE_9__ {scalar_t__ buflen; char* buf; } ;
typedef  TYPE_2__ conn_t ;
struct TYPE_10__ {scalar_t__ num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int HTTP_MAX_CONT_LINES ; 
 int fetch_getln (TYPE_2__*) ; 
 scalar_t__ hdr_end ; 
 TYPE_6__* hdr_names ; 
 scalar_t__ hdr_syserror ; 
 scalar_t__ hdr_unknown ; 
 int /*<<< orphan*/  http_conn_trimright (TYPE_2__*) ; 
 char* http_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* realloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static hdr_t
http_next_header(conn_t *conn, http_headerbuf_t *hbuf, const char **p)
{
	unsigned int i, len;

	/*
	 * Have to do the stripping here because of the first line. So
	 * it's done twice for the subsequent lines. No big deal
	 */
	http_conn_trimright(conn);
	if (conn->buflen == 0)
		return (hdr_end);

	/* Copy the line to the headerbuf */
	if (hbuf->bufsize < conn->buflen + 1) {
		if ((hbuf->buf = realloc(hbuf->buf, conn->buflen + 1)) == NULL)
			return (hdr_syserror);
		hbuf->bufsize = conn->buflen + 1;
	}
	strcpy(hbuf->buf, conn->buf);
	hbuf->buflen = conn->buflen;

	/*
	 * Fetch possible continuation lines. Stop at 1st non-continuation
	 * and leave it in the conn buffer
	 */
	for (i = 0; i < HTTP_MAX_CONT_LINES; i++) {
		if (fetch_getln(conn) == -1)
			return (hdr_syserror);

		/*
		 * Note: we carry on the idea from the previous version
		 * that a pure whitespace line is equivalent to an empty
		 * one (so it's not continuation and will be handled when
		 * we are called next)
		 */
		http_conn_trimright(conn);
		if (conn->buf[0] != ' ' && conn->buf[0] != "\t"[0])
			break;

		/* Got a continuation line. Concatenate to previous */
		len = hbuf->buflen + conn->buflen;
		if (hbuf->bufsize < len + 1) {
			len *= 2;
			if ((hbuf->buf = realloc(hbuf->buf, len + 1)) == NULL)
				return (hdr_syserror);
			hbuf->bufsize = len + 1;
		}
		strcpy(hbuf->buf + hbuf->buflen, conn->buf);
		hbuf->buflen += conn->buflen;
	}

	/*
	 * We could check for malformed headers but we don't really care.
	 * A valid header starts with a token immediately followed by a
	 * colon; a token is any sequence of non-control, non-whitespace
	 * characters except "()<>@,;:\\\"{}".
	 */
	for (i = 0; hdr_names[i].num != hdr_unknown; i++)
		if ((*p = http_match(hdr_names[i].name, hbuf->buf)) != NULL)
			return (hdr_names[i].num);

	return (hdr_unknown);
}