#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
struct TYPE_14__ {int status; char* reason; TYPE_10__ headers; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h2o_res_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_15__ {int hpack_capacity; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ h2o_hpack_header_table_t ;
struct TYPE_16__ {scalar_t__ size; scalar_t__ bytes; } ;
typedef  TYPE_3__ h2o_buffer_t ;
struct TYPE_13__ {int /*<<< orphan*/  max_frame_size; } ;

/* Variables and functions */
 TYPE_11__ H2O_HTTP2_SETTINGS_DEFAULT ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_TE ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_3__**,scalar_t__) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_3__**) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_hpack_dispose_header_table (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_hpack_flatten_response (TYPE_3__**,TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_memis (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

void test_token_wo_hpack_id(void)
{
    h2o_mem_pool_t pool;
    h2o_mem_init_pool(&pool);
    h2o_hpack_header_table_t table = {NULL};
    table.hpack_capacity = 4096;
    h2o_res_t res = {0};
    h2o_buffer_t *buf;
    h2o_buffer_init(&buf, &h2o_socket_buffer_prototype);

    res.status = 200;
    res.reason = "OK";
    h2o_add_header(&pool, &res.headers, H2O_TOKEN_TE, NULL, H2O_STRLIT("test"));

    h2o_hpack_flatten_response(&buf, &table, 1, H2O_HTTP2_SETTINGS_DEFAULT.max_frame_size, res.status, res.headers.entries,
                               res.headers.size, NULL, SIZE_MAX);
    ok(h2o_memis(buf->bytes + 9, buf->size - 9,
                 H2O_STRLIT("\x88"     /* :status:200 */
                            "\x40\x02" /* literal header w. incremental indexing, raw, TE */
                            "te"
                            "\x83" /* header value, huffman */
                            "IP\x9f" /* test */)));
    h2o_buffer_consume(&buf, buf->size);
    h2o_hpack_flatten_response(&buf, &table, 1, H2O_HTTP2_SETTINGS_DEFAULT.max_frame_size, res.status, res.headers.entries,
                               res.headers.size, NULL, SIZE_MAX);
    ok(h2o_memis(buf->bytes + 9, buf->size - 9,
                 H2O_STRLIT("\x88" /* :status:200 */
                            "\xbe" /* te: test, indexed */)));

    h2o_buffer_dispose(&buf);
    h2o_hpack_dispose_header_table(&table);
    h2o_mem_clear_pool(&pool);
}