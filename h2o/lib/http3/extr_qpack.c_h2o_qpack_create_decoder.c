#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int header_table_size; int max_entries; int /*<<< orphan*/  blocked_streams; int /*<<< orphan*/  table; int /*<<< orphan*/  max_blocked; scalar_t__ total_inserts; scalar_t__ insert_count; } ;
typedef  TYPE_1__ h2o_qpack_decoder_t ;

/* Variables and functions */
 TYPE_1__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  header_table_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

h2o_qpack_decoder_t *h2o_qpack_create_decoder(uint32_t header_table_size, uint16_t max_blocked)
{
    h2o_qpack_decoder_t *qpack = h2o_mem_alloc(sizeof(*qpack));

    qpack->insert_count = 0;
    qpack->header_table_size = header_table_size;
    qpack->max_entries = header_table_size / 32;
    qpack->total_inserts = 0;
    qpack->max_blocked = max_blocked;
    header_table_init(&qpack->table, qpack->header_table_size);
    memset(&qpack->blocked_streams, 0, sizeof(qpack->blocked_streams));

    return qpack;
}