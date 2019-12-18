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
struct comm_point {scalar_t__ type; scalar_t__ ssl_shake_state; int /*<<< orphan*/  buffer; int /*<<< orphan*/  http_is_chunked; scalar_t__ http_in_chunk_headers; scalar_t__ http_in_headers; scalar_t__ ssl; int /*<<< orphan*/  tcp_is_reading; } ;

/* Variables and functions */
 scalar_t__ comm_http ; 
 scalar_t__ comm_ssl_shake_none ; 
 int http_chunked_segment (struct comm_point*) ; 
 int /*<<< orphan*/  http_header_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_moveover_buffer (int /*<<< orphan*/ ) ; 
 int http_nonchunk_segment (struct comm_point*) ; 
 int http_process_chunk_header (struct comm_point*) ; 
 int /*<<< orphan*/  http_process_initial_header (struct comm_point*) ; 
 int /*<<< orphan*/  http_read_more (int,struct comm_point*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake (struct comm_point*) ; 
 int /*<<< orphan*/  ssl_http_read_more (struct comm_point*) ; 

__attribute__((used)) static int
comm_point_http_handle_read(int fd, struct comm_point* c)
{
	log_assert(c->type == comm_http);
	log_assert(fd != -1);

	/* if we are in ssl handshake, handle SSL handshake */
#ifdef HAVE_SSL
	if(c->ssl && c->ssl_shake_state != comm_ssl_shake_none) {
		if(!ssl_handshake(c))
			return 0;
		if(c->ssl_shake_state != comm_ssl_shake_none)
			return 1;
	}
#endif /* HAVE_SSL */

	if(!c->tcp_is_reading)
		return 1;
	/* read more data */
	if(c->ssl) {
		if(!ssl_http_read_more(c))
			return 0;
	} else {
		if(!http_read_more(fd, c))
			return 0;
	}

	sldns_buffer_flip(c->buffer);
	while(sldns_buffer_remaining(c->buffer) > 0) {
		/* if we are reading headers, read more headers */
		if(c->http_in_headers || c->http_in_chunk_headers) {
			/* if header is done, process the header */
			if(!http_header_done(c->buffer)) {
				/* copy remaining data to front of buffer
				 * and set rest for writing into it */
				http_moveover_buffer(c->buffer);
				/* return and wait to read more */
				return 1;
			}
			if(!c->http_in_chunk_headers) {
				/* process initial headers */
				if(!http_process_initial_header(c))
					return 0;
			} else {
				/* process chunk headers */
				int r = http_process_chunk_header(c);
				if(r == 0) return 0;
				if(r == 2) return 1; /* done */
				/* r == 1, continue */
			}
			/* see if we have more to process */
			continue;
		}

		if(!c->http_is_chunked) {
			/* if we are reading nonchunks, process that*/
			return http_nonchunk_segment(c);
		} else {
			/* if we are reading chunks, read the chunk */
			int r = http_chunked_segment(c);
			if(r == 0) return 0;
			if(r == 1) return 1;
			continue;
		}
	}
	/* broke out of the loop; could not process header instead need
	 * to read more */
	/* moveover any remaining data and read more data */
	http_moveover_buffer(c->buffer);
	/* return and wait to read more */
	return 1;
}