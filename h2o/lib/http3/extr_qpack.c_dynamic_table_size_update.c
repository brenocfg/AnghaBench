#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ max_size; } ;
struct TYPE_4__ {scalar_t__ header_table_size; TYPE_2__ table; } ;
typedef  TYPE_1__ h2o_qpack_decoder_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 
 char* h2o_qpack_err_invalid_max_size ; 
 int /*<<< orphan*/  header_table_evict (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dynamic_table_size_update(h2o_qpack_decoder_t *qpack, int64_t max_size, const char **err_desc)
{
    if (max_size > qpack->header_table_size) {
        *err_desc = h2o_qpack_err_invalid_max_size;
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    }

    qpack->table.max_size = max_size;
    header_table_evict(&qpack->table, 0);
    return 0;
}