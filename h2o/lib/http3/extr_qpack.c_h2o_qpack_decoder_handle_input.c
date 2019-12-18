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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {size_t size; TYPE_4__* entries; } ;
struct TYPE_12__ {size_t num_unblocked; TYPE_1__ list; } ;
struct TYPE_13__ {scalar_t__ total_inserts; TYPE_2__ blocked_streams; } ;
typedef  TYPE_3__ h2o_qpack_decoder_t ;
struct TYPE_14__ {scalar_t__ largest_ref; int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_INCOMPLETE ; 
 int decode_int (int /*<<< orphan*/ *,int const**,int const*,int) ; 
 int duplicate (TYPE_3__*,int /*<<< orphan*/ ,char const**) ; 
 int dynamic_table_size_update (TYPE_3__*,int /*<<< orphan*/ ,char const**) ; 
 int insert_with_name_reference (TYPE_3__*,int,int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ,char const**) ; 
 int insert_without_name_reference (TYPE_3__*,int,int const*,int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 

int h2o_qpack_decoder_handle_input(h2o_qpack_decoder_t *qpack, int64_t **unblocked_stream_ids, size_t *num_unblocked,
                                   const uint8_t **_src, const uint8_t *src_end, const char **err_desc)
{
    if (qpack->blocked_streams.num_unblocked != 0) {
        size_t remaining = qpack->blocked_streams.list.size - qpack->blocked_streams.num_unblocked;
        if (remaining != 0)
            memmove(qpack->blocked_streams.list.entries, qpack->blocked_streams.list.entries + remaining,
                    sizeof(qpack->blocked_streams.list.entries[0]) * remaining);
        qpack->blocked_streams.list.size = remaining;
        qpack->blocked_streams.num_unblocked = 0;
    }

    const uint8_t *src = *_src;
    int ret = 0;

    while (src != src_end && ret == 0) {
        switch (*src >> 5) {
        default: /* insert with name reference */ {
            int64_t name_index, value_len;
            int name_is_static = (*src & 0x40) != 0;
            if ((ret = decode_int(&name_index, &src, src_end, 6)) != 0)
                goto Exit;
            if (src == src_end)
                goto Exit;
            int value_is_huff = (*src & 0x80) != 0;
            if ((ret = decode_int(&value_len, &src, src_end, 7)) != 0)
                goto Exit;
            if (!(src + value_len <= src_end))
                goto Exit;
            ret = insert_with_name_reference(qpack, name_is_static, name_index, value_is_huff, src, value_len, err_desc);
            src += value_len;
        } break;
        case 2:
        case 3: /* insert without name reference */ {
            int64_t name_len, value_len;
            int name_is_huff = (*src & 0x20) != 0;
            if ((ret = decode_int(&name_len, &src, src_end, 5)) != 0)
                goto Exit;
            if (!(src + name_len < src_end))
                goto Exit;
            const uint8_t *name = src;
            src += name_len;
            int value_is_huff = (*src & 0x80) != 0;
            if ((ret = decode_int(&value_len, &src, src_end, 7)) != 0)
                goto Exit;
            if (!(src + value_len <= src_end))
                goto Exit;
            ret = insert_without_name_reference(qpack, name_is_huff, name, name_len, value_is_huff, src, value_len, err_desc);
            src += value_len;
        } break;
        case 0: /* duplicate */ {
            int64_t index;
            if ((ret = decode_int(&index, &src, src_end, 5)) != 0)
                goto Exit;
            ret = duplicate(qpack, index, err_desc);
        } break;
        case 1: /* dynamic table size update */ {
            int64_t max_size;
            if ((ret = decode_int(&max_size, &src, src_end, 5)) != 0)
                goto Exit;
            ret = dynamic_table_size_update(qpack, max_size, err_desc);
        } break;
        }
        *_src = src;
    }

Exit:
    if (ret == H2O_HTTP2_ERROR_INCOMPLETE)
        ret = 0;
    if (ret == 0) {
        /* build list of newly unblocked streams ids reusing the memory of the blocked streams list (nasty!) */
        *unblocked_stream_ids = &qpack->blocked_streams.list.entries[0].stream_id;
        for (qpack->blocked_streams.num_unblocked = 0; qpack->blocked_streams.num_unblocked < qpack->blocked_streams.list.size;
             ++qpack->blocked_streams.num_unblocked) {
            if (qpack->blocked_streams.list.entries[qpack->blocked_streams.num_unblocked].largest_ref > qpack->total_inserts)
                break;
            (*unblocked_stream_ids)[qpack->blocked_streams.num_unblocked] =
                qpack->blocked_streams.list.entries[qpack->blocked_streams.num_unblocked].stream_id;
        }
        *num_unblocked = qpack->blocked_streams.num_unblocked;
    }
    return (int)ret;
}