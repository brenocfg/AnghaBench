#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evhttp_request {size_t headers_size; int kind; TYPE_1__* evcon; } ;
struct evbuffer {int dummy; } ;
typedef  enum message_read_status { ____Placeholder_message_read_status } message_read_status ;
struct TYPE_2__ {size_t max_headers_size; } ;

/* Variables and functions */
 int ALL_DATA_READ ; 
 int DATA_CORRUPTED ; 
 int DATA_TOO_LONG ; 
 int /*<<< orphan*/  EVBUFFER_EOL_CRLF ; 
#define  EVHTTP_REQUEST 129 
#define  EVHTTP_RESPONSE 128 
 int MORE_DATA_EXPECTED ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 
 char* evbuffer_readln (struct evbuffer*,size_t*,int /*<<< orphan*/ ) ; 
 int evhttp_parse_request_line (struct evhttp_request*,char*) ; 
 int evhttp_parse_response_line (struct evhttp_request*,char*) ; 
 int /*<<< orphan*/  mm_free (char*) ; 

enum message_read_status
evhttp_parse_firstline_(struct evhttp_request *req, struct evbuffer *buffer)
{
	char *line;
	enum message_read_status status = ALL_DATA_READ;

	size_t line_length;
	/* XXX try */
	line = evbuffer_readln(buffer, &line_length, EVBUFFER_EOL_CRLF);
	if (line == NULL) {
		if (req->evcon != NULL &&
		    evbuffer_get_length(buffer) > req->evcon->max_headers_size)
			return (DATA_TOO_LONG);
		else
			return (MORE_DATA_EXPECTED);
	}

	if (req->evcon != NULL &&
	    line_length > req->evcon->max_headers_size) {
		mm_free(line);
		return (DATA_TOO_LONG);
	}

	req->headers_size = line_length;

	switch (req->kind) {
	case EVHTTP_REQUEST:
		if (evhttp_parse_request_line(req, line) == -1)
			status = DATA_CORRUPTED;
		break;
	case EVHTTP_RESPONSE:
		if (evhttp_parse_response_line(req, line) == -1)
			status = DATA_CORRUPTED;
		break;
	default:
		status = DATA_CORRUPTED;
	}

	mm_free(line);
	return (status);
}