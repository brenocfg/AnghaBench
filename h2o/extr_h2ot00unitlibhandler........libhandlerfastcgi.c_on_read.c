#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct st_fcgi_record_header_t {size_t contentLength; size_t paddingLength; int type; } ;
struct TYPE_14__ {int /*<<< orphan*/  inflight; } ;
struct TYPE_10__ {TYPE_7__ sending; TYPE_1__* receiving; } ;
struct st_fcgi_generator_t {int sent_headers; TYPE_4__* handler; TYPE_2__ resp; int /*<<< orphan*/  req; } ;
struct TYPE_13__ {TYPE_8__* input; struct st_fcgi_generator_t* data; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_15__ {size_t size; int /*<<< orphan*/  bytes; } ;
struct TYPE_11__ {int /*<<< orphan*/  io_timeout; } ;
struct TYPE_12__ {TYPE_3__ config; } ;
struct TYPE_9__ {scalar_t__ size; } ;

/* Variables and functions */
#define  FCGI_END_REQUEST 130 
 size_t FCGI_RECORD_HEADER_SIZE ; 
#define  FCGI_STDERR 129 
#define  FCGI_STDOUT 128 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  decode_header (struct st_fcgi_record_header_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_send (struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  errorclose (struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_8__**,size_t) ; 
 int /*<<< orphan*/  h2o_doublebuffer_prepare_empty (TYPE_7__*) ; 
 int /*<<< orphan*/  h2o_req_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  h2o_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_stdin_record (struct st_fcgi_generator_t*,struct st_fcgi_record_header_t*) ; 
 int /*<<< orphan*/  on_rw_timeout ; 
 int /*<<< orphan*/  send_eos_and_close (struct st_fcgi_generator_t*,int) ; 
 int /*<<< orphan*/  set_timeout (struct st_fcgi_generator_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_read(h2o_socket_t *sock, const char *err)
{
    struct st_fcgi_generator_t *generator = sock->data;
    int can_keepalive = 0;
    int sent_headers_before = generator->sent_headers;

    if (err != NULL) {
        /* note: FastCGI server is allowed to close the connection any time after sending an empty FCGI_STDOUT record */
        if (!generator->sent_headers)
            h2o_req_log_error(generator->req, MODULE_NAME, "fastcgi connection closed unexpectedly");
        errorclose(generator);
        return;
    }

    /* handle the records */
    while (1) {
        struct st_fcgi_record_header_t header;
        size_t recsize;
        if (sock->input->size < FCGI_RECORD_HEADER_SIZE)
            break;
        decode_header(&header, sock->input->bytes);
        recsize = FCGI_RECORD_HEADER_SIZE + header.contentLength + header.paddingLength;
        if (sock->input->size < recsize)
            break;
        /* we have a complete record */
        switch (header.type) {
        case FCGI_STDOUT:
            if (handle_stdin_record(generator, &header) != 0)
                goto Error;
            h2o_buffer_consume(&sock->input, recsize);
            break;
        case FCGI_STDERR:
            if (header.contentLength != 0)
                h2o_req_log_error(generator->req, MODULE_NAME, "%.*s", (int)header.contentLength,
                                  sock->input->bytes + FCGI_RECORD_HEADER_SIZE);
            h2o_buffer_consume(&sock->input, recsize);
            break;
        case FCGI_END_REQUEST:
            if (!generator->sent_headers) {
                h2o_req_log_error(generator->req, MODULE_NAME, "received FCGI_END_REQUEST before end of the headers");
                goto Error;
            }
            h2o_buffer_consume(&sock->input, recsize);
            can_keepalive = 1;
            goto EOS_Received;
        default:
            h2o_req_log_error(generator->req, MODULE_NAME, "received unexpected record, type: %u", header.type);
            h2o_buffer_consume(&sock->input, recsize);
            if (!generator->sent_headers)
                goto Error;
            goto EOS_Received;
        }
    }

    /* send data if necessary */
    if (generator->sent_headers) {
        if (!sent_headers_before && generator->resp.receiving->size == 0) {
            /* send headers immediately */
            h2o_doublebuffer_prepare_empty(&generator->resp.sending);
            h2o_send(generator->req, NULL, 0, H2O_SEND_STATE_IN_PROGRESS);
        } else if (!generator->resp.sending.inflight) {
            do_send(generator);
        }
    }

    set_timeout(generator, generator->handler->config.io_timeout, on_rw_timeout);
    return;

EOS_Received:
    send_eos_and_close(generator, can_keepalive);
    return;

Error:
    errorclose(generator);
}