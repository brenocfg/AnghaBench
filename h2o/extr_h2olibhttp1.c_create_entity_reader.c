#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t content_length; } ;
struct TYPE_7__ {TYPE_2__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_4__ req; TYPE_3__ super; } ;
struct phr_header {int name_len; int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {TYPE_1__* globalconf; } ;
struct TYPE_5__ {size_t max_request_entity_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 size_t SIZE_MAX ; 
 int create_chunked_entity_reader (struct st_h2o_http1_conn_t*) ; 
 int create_content_length_entity_reader (struct st_h2o_http1_conn_t*,size_t) ; 
 int /*<<< orphan*/  entity_read_send_error_400 (struct st_h2o_http1_conn_t*,char*,char*) ; 
 int /*<<< orphan*/  entity_read_send_error_413 (struct st_h2o_http1_conn_t*,char*,char*) ; 
 int /*<<< orphan*/  h2o_lcstris (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t h2o_strtosize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_entity_reader(struct st_h2o_http1_conn_t *conn, const struct phr_header *entity_header)
{
    /* strlen("content-length") is unequal to sizeof("transfer-encoding"), and thus checking the length only is sufficient */
    if (entity_header->name_len == sizeof("transfer-encoding") - 1) {
        /* transfer-encoding */
        if (!h2o_lcstris(entity_header->value, entity_header->value_len, H2O_STRLIT("chunked"))) {
            entity_read_send_error_400(conn, "Invalid Request", "unknown transfer-encoding");
            return -1;
        }
        return create_chunked_entity_reader(conn);
    } else {
        /* content-length */
        size_t content_length = h2o_strtosize(entity_header->value, entity_header->value_len);
        if (content_length == SIZE_MAX) {
            entity_read_send_error_400(conn, "Invalid Request", "broken content-length header");
            return -1;
        }
        if (content_length > conn->super.ctx->globalconf->max_request_entity_size) {
            entity_read_send_error_413(conn, "Request Entity Too Large", "request entity is too large");
            return -1;
        }
        conn->req.content_length = content_length;
        return create_content_length_entity_reader(conn, (size_t)content_length);
    }
    /* failed */
    return -1;
}