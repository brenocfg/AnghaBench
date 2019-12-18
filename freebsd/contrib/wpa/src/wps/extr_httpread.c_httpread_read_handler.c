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
struct httpread {int got_hdr; scalar_t__ body_nbytes; int content_length; int got_body; char* hdr; int hdr_nbytes; scalar_t__ max_bytes; scalar_t__ body_alloc_nbytes; char* body; int in_chunk_data; int chunk_start; scalar_t__ chunk_size; int in_trailer; int trailer_state; scalar_t__ hdr_type; int got_file; int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* cb ) (struct httpread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sd; scalar_t__ chunked; scalar_t__ got_content_length; } ;
typedef  int /*<<< orphan*/  readbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int HTTPREAD_BODYBUF_DELTA ; 
 int /*<<< orphan*/  HTTPREAD_EVENT_ERROR ; 
 int /*<<< orphan*/  HTTPREAD_EVENT_FILE_READY ; 
 int HTTPREAD_HEADER_MAX_SIZE ; 
 int HTTPREAD_READBUF_SIZE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct httpread*) ; 
 int /*<<< orphan*/  eloop_unregister_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ httpread_hdr_analyze (struct httpread*) ; 
 int /*<<< orphan*/  httpread_timeout_handler ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 char* os_realloc (char*,int) ; 
 int /*<<< orphan*/  os_strncasecmp (char*,char*,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct httpread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct httpread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  trailer_empty_cr 131 
#define  trailer_line_begin 130 
#define  trailer_nonempty 129 
#define  trailer_nonempty_cr 128 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void httpread_read_handler(int sd, void *eloop_ctx, void *sock_ctx)
{
	struct httpread *h = sock_ctx;
	int nread;
	char *rbp;      /* pointer into read buffer */
	char *hbp;      /* pointer into header buffer */
	char *bbp;      /* pointer into body buffer */
	char readbuf[HTTPREAD_READBUF_SIZE];  /* temp use to read into */

	/* read some at a time, then search for the interal
	 * boundaries between header and data and etc.
	 */
	wpa_printf(MSG_DEBUG, "httpread: Trying to read more data(%p)", h);
	nread = read(h->sd, readbuf, sizeof(readbuf));
	if (nread < 0) {
		wpa_printf(MSG_DEBUG, "httpread failed: %s", strerror(errno));
		goto bad;
	}
	wpa_hexdump_ascii(MSG_MSGDUMP, "httpread - read", readbuf, nread);
	if (nread == 0) {
		/* end of transmission... this may be normal
		 * or may be an error... in some cases we can't
		 * tell which so we must assume it is normal then.
		 */
		if (!h->got_hdr) {
			/* Must at least have completed header */
			wpa_printf(MSG_DEBUG, "httpread premature eof(%p)", h);
			goto bad;
		}
		if (h->chunked || h->got_content_length) {
			/* Premature EOF; e.g. dropped connection */
			wpa_printf(MSG_DEBUG,
				   "httpread premature eof(%p) %d/%d",
				   h, h->body_nbytes,
				   h->content_length);
			goto bad;
		}
		/* No explicit length, hopefully we have all the data
		 * although dropped connections can cause false
		 * end
		 */
		wpa_printf(MSG_DEBUG, "httpread ok eof(%p)", h);
		h->got_body = 1;
		goto got_file;
	}
	rbp = readbuf;

	/* Header consists of text lines (terminated by both CR and LF)
	 * and an empty line (CR LF only).
	 */
	if (!h->got_hdr) {
		hbp = h->hdr + h->hdr_nbytes;
		/* add to headers until:
		 *      -- we run out of data in read buffer
		 *      -- or, we run out of header buffer room
		 *      -- or, we get double CRLF in headers
		 */
		for (;;) {
			if (nread == 0)
				goto get_more;
			if (h->hdr_nbytes == HTTPREAD_HEADER_MAX_SIZE) {
				wpa_printf(MSG_DEBUG,
					   "httpread: Too long header");
				goto bad;
			}
			*hbp++ = *rbp++;
			nread--;
			h->hdr_nbytes++;
			if (h->hdr_nbytes >= 4 &&
			    hbp[-1] == '\n' &&
			    hbp[-2] == '\r' &&
			    hbp[-3] == '\n' &&
			    hbp[-4] == '\r' ) {
				h->got_hdr = 1;
				*hbp = 0;       /* null terminate */
				break;
			}
		}
		/* here we've just finished reading the header */
		if (httpread_hdr_analyze(h)) {
			wpa_printf(MSG_DEBUG, "httpread bad hdr(%p)", h);
			goto bad;
		}
		if (h->max_bytes == 0) {
			wpa_printf(MSG_DEBUG, "httpread no body hdr end(%p)",
				   h);
			goto got_file;
		}
		if (h->got_content_length && h->content_length == 0) {
			wpa_printf(MSG_DEBUG,
				   "httpread zero content length(%p)", h);
			goto got_file;
		}
	}

	/* Certain types of requests never have data and so
	 * must be specially recognized.
	 */
	if (!os_strncasecmp(h->hdr, "SUBSCRIBE", 9) ||
	    !os_strncasecmp(h->hdr, "UNSUBSCRIBE", 11) ||
	    !os_strncasecmp(h->hdr, "HEAD", 4) ||
	    !os_strncasecmp(h->hdr, "GET", 3)) {
		if (!h->got_body) {
			wpa_printf(MSG_DEBUG, "httpread NO BODY for sp. type");
		}
		h->got_body = 1;
		goto got_file;
	}

	/* Data can be just plain binary data, or if "chunked"
	 * consists of chunks each with a header, ending with
	 * an ending header.
	 */
	if (nread == 0)
		goto get_more;
	if (!h->got_body) {
		/* Here to get (more of) body */
		/* ensure we have enough room for worst case for body
		 * plus a null termination character
		 */
		if (h->body_alloc_nbytes < (h->body_nbytes + nread + 1)) {
			char *new_body;
			int new_alloc_nbytes;

			if (h->body_nbytes >= h->max_bytes) {
				wpa_printf(MSG_DEBUG,
					   "httpread: body_nbytes=%d >= max_bytes=%d",
					   h->body_nbytes, h->max_bytes);
				goto bad;
			}
			new_alloc_nbytes = h->body_alloc_nbytes +
				HTTPREAD_BODYBUF_DELTA;
			/* For content-length case, the first time
			 * through we allocate the whole amount
			 * we need.
			 */
			if (h->got_content_length &&
			    new_alloc_nbytes < (h->content_length + 1))
				new_alloc_nbytes = h->content_length + 1;
			if (new_alloc_nbytes < h->body_alloc_nbytes ||
			    new_alloc_nbytes > h->max_bytes +
			    HTTPREAD_BODYBUF_DELTA) {
				wpa_printf(MSG_DEBUG,
					   "httpread: Unacceptable body length %d (body_alloc_nbytes=%u max_bytes=%u)",
					   new_alloc_nbytes,
					   h->body_alloc_nbytes,
					   h->max_bytes);
				goto bad;
			}
			if ((new_body = os_realloc(h->body, new_alloc_nbytes))
			    == NULL) {
				wpa_printf(MSG_DEBUG,
					   "httpread: Failed to reallocate buffer (len=%d)",
					   new_alloc_nbytes);
				goto bad;
			}

			h->body = new_body;
			h->body_alloc_nbytes = new_alloc_nbytes;
		}
		/* add bytes */
		bbp = h->body + h->body_nbytes;
		for (;;) {
			int ncopy;
			/* See if we need to stop */
			if (h->chunked && h->in_chunk_data == 0) {
				/* in chunk header */
				char *cbp = h->body + h->chunk_start;
				if (bbp-cbp >= 2 && bbp[-2] == '\r' &&
				    bbp[-1] == '\n') {
					/* end of chunk hdr line */
					/* hdr line consists solely
					 * of a hex numeral and CFLF
					 */
					if (!isxdigit(*cbp)) {
						wpa_printf(MSG_DEBUG,
							   "httpread: Unexpected chunk header value (not a hex digit)");
						goto bad;
					}
					h->chunk_size = strtoul(cbp, NULL, 16);
					if (h->chunk_size < 0 ||
					    h->chunk_size > h->max_bytes) {
						wpa_printf(MSG_DEBUG,
							   "httpread: Invalid chunk size %d",
							   h->chunk_size);
						goto bad;
					}
					/* throw away chunk header
					 * so we have only real data
					 */
					h->body_nbytes = h->chunk_start;
					bbp = cbp;
					if (h->chunk_size == 0) {
						/* end of chunking */
						/* trailer follows */
						h->in_trailer = 1;
						wpa_printf(MSG_DEBUG,
							   "httpread end chunks(%p)",
							   h);
						break;
					}
					h->in_chunk_data = 1;
					/* leave chunk_start alone */
				}
			} else if (h->chunked) {
				/* in chunk data */
				if ((h->body_nbytes - h->chunk_start) ==
				    (h->chunk_size + 2)) {
					/* end of chunk reached,
					 * new chunk starts
					 */
					/* check chunk ended w/ CRLF
					 * which we'll throw away
					 */
					if (bbp[-1] == '\n' &&
					    bbp[-2] == '\r') {
					} else {
						wpa_printf(MSG_DEBUG,
							   "httpread: Invalid chunk end");
						goto bad;
					}
					h->body_nbytes -= 2;
					bbp -= 2;
					h->chunk_start = h->body_nbytes;
					h->in_chunk_data = 0;
					h->chunk_size = 0; /* just in case */
				}
			} else if (h->got_content_length &&
				   h->body_nbytes >= h->content_length) {
				h->got_body = 1;
				wpa_printf(MSG_DEBUG,
					   "httpread got content(%p)", h);
				goto got_file;
			}
			if (nread <= 0)
				break;
			/* Now transfer. Optimize using memcpy where we can. */
			if (h->chunked && h->in_chunk_data) {
				/* copy up to remainder of chunk data
				 * plus the required CR+LF at end
				 */
				ncopy = (h->chunk_start + h->chunk_size + 2) -
					h->body_nbytes;
			} else if (h->chunked) {
				/*in chunk header -- don't optimize */
				*bbp++ = *rbp++;
				nread--;
				h->body_nbytes++;
				continue;
			} else if (h->got_content_length) {
				ncopy = h->content_length - h->body_nbytes;
			} else {
				ncopy = nread;
			}
			/* Note: should never be 0 */
			if (ncopy < 0) {
				wpa_printf(MSG_DEBUG,
					   "httpread: Invalid ncopy=%d", ncopy);
				goto bad;
			}
			if (ncopy > nread)
				ncopy = nread;
			os_memcpy(bbp, rbp, ncopy);
			bbp += ncopy;
			h->body_nbytes += ncopy;
			rbp += ncopy;
			nread -= ncopy;
		}       /* body copy loop */
	}       /* !got_body */
	if (h->chunked && h->in_trailer) {
		/* If "chunked" then there is always a trailer,
		 * consisting of zero or more non-empty lines
		 * ending with CR LF and then an empty line w/ CR LF.
		 * We do NOT support trailers except to skip them --
		 * this is supported (generally) by the http spec.
		 */
		for (;;) {
			int c;
			if (nread <= 0)
				break;
			c = *rbp++;
			nread--;
			switch (h->trailer_state) {
			case trailer_line_begin:
				if (c == '\r')
					h->trailer_state = trailer_empty_cr;
				else
					h->trailer_state = trailer_nonempty;
				break;
			case trailer_empty_cr:
				/* end empty line */
				if (c == '\n') {
					h->trailer_state = trailer_line_begin;
					h->in_trailer = 0;
					wpa_printf(MSG_DEBUG,
						   "httpread got content(%p)",
						   h);
					h->got_body = 1;
					goto got_file;
				}
				h->trailer_state = trailer_nonempty;
				break;
			case trailer_nonempty:
				if (c == '\r')
					h->trailer_state = trailer_nonempty_cr;
				break;
			case trailer_nonempty_cr:
				if (c == '\n')
					h->trailer_state = trailer_line_begin;
				else
					h->trailer_state = trailer_nonempty;
				break;
			}
		}
	}
	goto get_more;

bad:
	/* Error */
	wpa_printf(MSG_DEBUG, "httpread read/parse failure (%p)", h);
	(*h->cb)(h, h->cookie, HTTPREAD_EVENT_ERROR);
	return;

get_more:
	wpa_printf(MSG_DEBUG, "httpread: get more (%p)", h);
	return;

got_file:
	wpa_printf(MSG_DEBUG, "httpread got file %d bytes type %d",
		   h->body_nbytes, h->hdr_type);
	wpa_hexdump_ascii(MSG_MSGDUMP, "httpread: body",
			  h->body, h->body_nbytes);
	/* Null terminate for convenience of some applications */
	if (h->body)
		h->body[h->body_nbytes] = 0; /* null terminate */
	h->got_file = 1;
	/* Assume that we do NOT support keeping connection alive,
	 * and just in case somehow we don't get destroyed right away,
	 * unregister now.
	 */
	eloop_unregister_sock(h->sd, EVENT_TYPE_READ);
	/* The application can destroy us whenever they feel like...
	 * cancel timeout.
	 */
	eloop_cancel_timeout(httpread_timeout_handler, NULL, h);
	(*h->cb)(h, h->cookie, HTTPREAD_EVENT_FILE_READY);
}