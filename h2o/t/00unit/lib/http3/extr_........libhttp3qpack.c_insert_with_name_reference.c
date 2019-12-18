#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_qpack_header_t {TYPE_8__* name; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  h2o_token_t ;
struct TYPE_9__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ h2o_qpack_static_table_entry_t ;
struct TYPE_11__ {scalar_t__ base_offset; scalar_t__ last; scalar_t__ first; } ;
struct TYPE_10__ {TYPE_4__ table; } ;
typedef  TYPE_2__ h2o_qpack_decoder_t ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 
 scalar_t__ MAX_HEADER_VALUE_LENGTH ; 
 scalar_t__ h2o_iovec_is_token (TYPE_8__*) ; 
 char* h2o_qpack_err_header_value_too_long ; 
 char* h2o_qpack_err_invalid_dynamic_reference ; 
 int insert_literal_header (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,scalar_t__,char const**) ; 
 int insert_token_header (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,scalar_t__,char const**) ; 
 struct st_h2o_qpack_header_t* resolve_dynamic_abs (TYPE_4__*,scalar_t__,char const**) ; 
 TYPE_1__* resolve_static_abs (scalar_t__,char const**) ; 

__attribute__((used)) static int insert_with_name_reference(h2o_qpack_decoder_t *qpack, int name_is_static, int64_t name_index, int value_is_huff,
                                      const uint8_t *value, int64_t value_len, const char **err_desc)
{
    if (value_len >= MAX_HEADER_VALUE_LENGTH) {
        *err_desc = h2o_qpack_err_header_value_too_long;
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    }

    if (name_is_static) {
        const h2o_qpack_static_table_entry_t *ref;
        if ((ref = resolve_static_abs(name_index, err_desc)) == NULL)
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        return insert_token_header(qpack, ref->name, value_is_huff, value, value_len, err_desc);
    } else {
        struct st_h2o_qpack_header_t *ref;
        int64_t base_index = qpack->table.base_offset + (qpack->table.last - qpack->table.first) - 1;
        if (name_index > base_index) {
            *err_desc = h2o_qpack_err_invalid_dynamic_reference;
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        }
        if ((ref = resolve_dynamic_abs(&qpack->table, base_index - name_index, err_desc)) == NULL)
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        if (h2o_iovec_is_token(ref->name)) {
            return insert_token_header(qpack, (h2o_token_t *)ref->name, value_is_huff, value, value_len, err_desc);
        } else {
            return insert_literal_header(qpack, ref->name->base, ref->name->len, value_is_huff, value, value_len, err_desc);
        }
    }
}