#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  h2o_qpack_encoder_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_8__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_9__ {int size; int* entries; } ;
typedef  TYPE_2__ h2o_byte_vector_t ;

/* Variables and functions */
 int H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int /*<<< orphan*/  flatten_int (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flatten_string (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static void emit_insert_with_nameref(h2o_qpack_encoder_t *qpack, h2o_mem_pool_t *pool, h2o_byte_vector_t *buf, int is_static,
                                     int64_t index, h2o_iovec_t value)
{
    h2o_vector_reserve(pool, buf, buf->size + (H2O_HPACK_ENCODE_INT_MAX_LENGTH * 2) + value.len);
    buf->entries[buf->size] = 0x80 | (is_static ? 0x40 : 0);
    flatten_int(buf, index, 6);
    flatten_string(buf, value.base, value.len, 7, 0);
}