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
struct comm_reply {int /*<<< orphan*/  c; } ;
struct comm_point {size_t http_stored; size_t tcp_byte_count; int http_in_chunk_headers; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ;int /*<<< orphan*/  buffer; int /*<<< orphan*/  http_temp; struct comm_reply repinfo; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*)) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 size_t sldns_buffer_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 size_t sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ; 
 int /*<<< orphan*/  stub2 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ; 

__attribute__((used)) static int
http_chunked_segment(struct comm_point* c)
{
	/* the c->buffer has from position..limit new data we read. */
	/* the current chunk has length tcp_byte_count.
	 * once we read that read more chunk headers.
	 */
	size_t remainbufferlen;
	size_t got_now = sldns_buffer_limit(c->buffer) - c->http_stored;
	if(c->tcp_byte_count <= got_now) {
		/* the chunk has completed (with perhaps some extra data
		 * from next chunk header and next chunk) */
		/* save too much info into temp buffer */
		size_t fraglen;
		struct comm_reply repinfo;
		c->http_stored = 0;
		sldns_buffer_skip(c->buffer, (ssize_t)c->tcp_byte_count);
		sldns_buffer_clear(c->http_temp);
		sldns_buffer_write(c->http_temp,
			sldns_buffer_current(c->buffer),
			sldns_buffer_remaining(c->buffer));
		sldns_buffer_flip(c->http_temp);

		/* callback with this fragment */
		fraglen = sldns_buffer_position(c->buffer);
		sldns_buffer_set_position(c->buffer, 0);
		sldns_buffer_set_limit(c->buffer, fraglen);
		repinfo = c->repinfo;
		fptr_ok(fptr_whitelist_comm_point(c->callback));
		(void)(*c->callback)(c, c->cb_arg, NETEVENT_NOERROR, &repinfo);
		/* c->callback has to buffer_clear(). */

		/* is commpoint deleted? */
		if(!repinfo.c) {
			return 1;
		}
		/* copy waiting info */
		sldns_buffer_clear(c->buffer);
		sldns_buffer_write(c->buffer,
			sldns_buffer_begin(c->http_temp),
			sldns_buffer_remaining(c->http_temp));
		sldns_buffer_flip(c->buffer);
		/* process end of chunk trailer header lines, until
		 * an empty line */
		c->http_in_chunk_headers = 3;
		/* process more data in buffer (if any) */
		return 2;
	}
	c->tcp_byte_count -= got_now;

	/* if we have the buffer space,
	 * read more data collected into the buffer */
	remainbufferlen = sldns_buffer_capacity(c->buffer) -
		sldns_buffer_limit(c->buffer);
	if(remainbufferlen >= c->tcp_byte_count ||
		remainbufferlen >= 2048) {
		size_t total = sldns_buffer_limit(c->buffer);
		sldns_buffer_clear(c->buffer);
		sldns_buffer_set_position(c->buffer, total);
		c->http_stored = total;
		/* return and wait to read more */
		return 1;
	}
	
	/* callback of http reader for a new part of the data */
	c->http_stored = 0;
	sldns_buffer_set_position(c->buffer, 0);
	fptr_ok(fptr_whitelist_comm_point(c->callback));
	(void)(*c->callback)(c, c->cb_arg, NETEVENT_NOERROR, NULL);
	/* c->callback has to buffer_clear(c->buffer). */
	/* return and wait to read more */
	return 1;
}