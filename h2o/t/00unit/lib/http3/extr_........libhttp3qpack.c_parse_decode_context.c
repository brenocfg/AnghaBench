#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int const uint64_t ;
typedef  int uint32_t ;
struct st_h2o_qpack_decode_header_ctx_t {int largest_ref; int base_index; TYPE_4__* qpack; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_9__ {TYPE_2__ list; } ;
struct TYPE_7__ {scalar_t__ base_offset; scalar_t__ last; scalar_t__ first; } ;
struct TYPE_10__ {int max_entries; int total_inserts; scalar_t__ max_blocked; TYPE_3__ blocked_streams; TYPE_1__ table; } ;
typedef  TYPE_4__ h2o_qpack_decoder_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_INCOMPLETE ; 
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ decode_int (int*,int const**,int const*,int) ; 
 int /*<<< orphan*/  decoder_link_blocked (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int parse_decode_context(h2o_qpack_decoder_t *qpack, struct st_h2o_qpack_decode_header_ctx_t *ctx, int64_t stream_id,
                                const uint8_t **src, const uint8_t *src_end)
{
    ctx->qpack = qpack;

    /* largest reference */
    if (decode_int(&ctx->largest_ref, src, src_end, 8) != 0)
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    if (ctx->largest_ref > 0) {
        if (qpack->max_entries == 0)
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        const uint32_t full_range = 2 * qpack->max_entries;
        uint64_t max_value = qpack->total_inserts + qpack->max_entries;
        uint64_t rounded = max_value / full_range * full_range;
        ctx->largest_ref += rounded - 1;
        if (ctx->largest_ref > max_value && ctx->largest_ref > full_range)
            ctx->largest_ref -= full_range;
        assert(ctx->largest_ref != 0);
    }

    /* base index */
    if (*src >= src_end)
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    int sign = (**src & 0x80) != 0;
    if (decode_int(&ctx->base_index, src, src_end, 7) != 0)
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    ctx->base_index = sign == 0 ? ctx->largest_ref + ctx->base_index : ctx->largest_ref - ctx->base_index - 1;

    /* is the stream blocked? */
    if (ctx->largest_ref >= qpack->table.base_offset + qpack->table.last - qpack->table.first) {
        if (qpack->blocked_streams.list.size + 1 >= qpack->max_blocked)
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        decoder_link_blocked(qpack, stream_id, ctx->largest_ref);
        return H2O_HTTP3_ERROR_INCOMPLETE;
    }

    return 0;
}