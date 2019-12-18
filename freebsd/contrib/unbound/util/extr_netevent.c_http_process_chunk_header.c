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
struct comm_point {int http_in_chunk_headers; scalar_t__ tcp_byte_count; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_DONE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 char* http_header_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_moveover_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
http_process_chunk_header(struct comm_point* c)
{
	char* line = http_header_line(c->buffer);
	if(!line) return 1;
	if(c->http_in_chunk_headers == 3) {
		verbose(VERB_ALGO, "http chunk trailer: %s", line);
		/* are we done ? */
		if(line[0] == 0 && c->tcp_byte_count == 0) {
			/* callback of http reader when NETEVENT_DONE,
			 * end of data, with no data in buffer */
			sldns_buffer_set_position(c->buffer, 0);
			sldns_buffer_set_limit(c->buffer, 0);
			fptr_ok(fptr_whitelist_comm_point(c->callback));
			(void)(*c->callback)(c, c->cb_arg, NETEVENT_DONE, NULL);
			/* return that we are done */
			return 2;
		}
		if(line[0] == 0) {
			/* continue with header of the next chunk */
			c->http_in_chunk_headers = 1;
			/* remove header text from front of buffer */
			http_moveover_buffer(c->buffer);
			sldns_buffer_flip(c->buffer);
			return 1;
		}
		/* ignore further trail headers */
		return 1;
	}
	verbose(VERB_ALGO, "http chunk header: %s", line);
	if(c->http_in_chunk_headers == 1) {
		/* read chunked start line */
		char* end = NULL;
		c->tcp_byte_count = (size_t)strtol(line, &end, 16);
		if(end == line)
			return 0;
		c->http_in_chunk_headers = 0;
		/* remove header text from front of buffer */
		http_moveover_buffer(c->buffer);
		sldns_buffer_flip(c->buffer);
		if(c->tcp_byte_count == 0) {
			/* done with chunks, process chunk_trailer lines */
			c->http_in_chunk_headers = 3;
		}
		return 1;
	}
	/* ignore other headers */
	return 1;
}