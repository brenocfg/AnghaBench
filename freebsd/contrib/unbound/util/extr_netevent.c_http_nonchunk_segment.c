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
struct comm_point {size_t http_stored; size_t tcp_byte_count; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_DONE ; 
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 size_t sldns_buffer_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 size_t sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
http_nonchunk_segment(struct comm_point* c)
{
	/* c->buffer at position..limit has new data we read in.
	 * the buffer itself is full of nonchunked data.
	 * we are looking to read tcp_byte_count more data
	 * and then the transfer is done. */
	size_t remainbufferlen;
	size_t got_now = sldns_buffer_limit(c->buffer) - c->http_stored;
	if(c->tcp_byte_count <= got_now) {
		/* done, this is the last data fragment */
		c->http_stored = 0;
		sldns_buffer_set_position(c->buffer, 0);
		fptr_ok(fptr_whitelist_comm_point(c->callback));
		(void)(*c->callback)(c, c->cb_arg, NETEVENT_DONE, NULL);
		return 1;
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
	/* call callback with this data amount, then
	 * wait for more */
	c->http_stored = 0;
	sldns_buffer_set_position(c->buffer, 0);
	fptr_ok(fptr_whitelist_comm_point(c->callback));
	(void)(*c->callback)(c, c->cb_arg, NETEVENT_NOERROR, NULL);
	/* c->callback has to buffer_clear(c->buffer). */
	/* return and wait to read more */
	return 1;
}