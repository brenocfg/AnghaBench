#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct st_h2o_qpack_header_t {TYPE_4__* name; int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; } ;
struct st_h2o_qpack_decode_header_ctx_t {int /*<<< orphan*/  base_index; TYPE_2__* qpack; } ;
struct TYPE_14__ {int /*<<< orphan*/ * base; } ;
struct TYPE_13__ {TYPE_1__* name; TYPE_4__ value; } ;
typedef  TYPE_3__ h2o_qpack_static_table_entry_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
struct TYPE_11__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 
 TYPE_4__* decode_header_name_literal (int /*<<< orphan*/ *,int const**,int const*,int,char const**) ; 
 TYPE_4__ decode_header_value_literal (int /*<<< orphan*/ *,int const**,int const*,char const**) ; 
 TYPE_4__ h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_link_shared (int /*<<< orphan*/ *,struct st_h2o_qpack_header_t*) ; 
 struct st_h2o_qpack_header_t* resolve_dynamic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const**,int const*,int,char const**) ; 
 struct st_h2o_qpack_header_t* resolve_dynamic_postbase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const**,int const*,int,char const**) ; 
 TYPE_3__* resolve_static (int const**,int const*,int,char const**) ; 

__attribute__((used)) static int decode_header(h2o_mem_pool_t *pool, void *_ctx, h2o_iovec_t **name, h2o_iovec_t *value, const uint8_t **src,
                         const uint8_t *src_end, const char **err_desc)
{
    struct st_h2o_qpack_decode_header_ctx_t *ctx = _ctx;

    switch (**src >> 4) {
    case 12:
    case 13:
    case 14:
    case 15: /* indexed static header field */ {
        const h2o_qpack_static_table_entry_t *entry;
        if ((entry = resolve_static(src, src_end, 6, err_desc)) == NULL)
            goto Fail;
        *name = (h2o_iovec_t *)&entry->name->buf;
        *value = entry->value;
    } break;
    case 8:
    case 9:
    case 10:
    case 11: /* indexed dynamic header field */ {
        struct st_h2o_qpack_header_t *entry;
        if ((entry = resolve_dynamic(&ctx->qpack->table, ctx->base_index, src, src_end, 6, err_desc)) == NULL)
            goto Fail;
        h2o_mem_link_shared(pool, entry);
        *name = entry->name;
        *value = h2o_iovec_init(entry->value, entry->value_len);
    } break;
    case 5:
    case 7: /* literal header field with static name reference */ {
        const h2o_qpack_static_table_entry_t *entry;
        if ((entry = resolve_static(src, src_end, 4, err_desc)) == NULL)
            goto Fail;
        *name = (h2o_iovec_t *)&entry->name->buf;
        if ((*value = decode_header_value_literal(pool, src, src_end, err_desc)).base == NULL)
            goto Fail;
    } break;
    case 4:
    case 6: /* literal header field with dynamic name reference */ {
        struct st_h2o_qpack_header_t *entry;
        if ((entry = resolve_dynamic(&ctx->qpack->table, ctx->base_index, src, src_end, 4, err_desc)) == NULL)
            goto Fail;
        h2o_mem_link_shared(pool, entry);
        *name = entry->name;
        if ((*value = decode_header_value_literal(pool, src, src_end, err_desc)).base == NULL)
            goto Fail;
    } break;
    case 2:
    case 3: /* literal header field without name reference */ {
        if ((*name = decode_header_name_literal(pool, src, src_end, 3, err_desc)) == NULL)
            goto Fail;
        if ((*value = decode_header_value_literal(pool, src, src_end, err_desc)).base == NULL)
            goto Fail;
    } break;
    case 1: /* indexed header field with post-base index */ {
        struct st_h2o_qpack_header_t *entry;
        if ((entry = resolve_dynamic_postbase(&ctx->qpack->table, ctx->base_index, src, src_end, 4, err_desc)) == NULL)
            goto Fail;
        h2o_mem_link_shared(pool, entry);
        *name = entry->name;
        *value = h2o_iovec_init(entry->value, entry->value_len);
    } break;
    case 0: /* literal header field with post-base name reference */ {
        struct st_h2o_qpack_header_t *entry;
        if ((entry = resolve_dynamic_postbase(&ctx->qpack->table, ctx->base_index, src, src_end, 3, err_desc)) == NULL)
            goto Fail;
        h2o_mem_link_shared(pool, entry);
        *name = entry->name;
        if ((*value = decode_header_value_literal(pool, src, src_end, err_desc)).base == NULL)
            goto Fail;
    } break;
    }

    return 0;
Fail:
    return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
}