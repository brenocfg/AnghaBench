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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  inflight; scalar_t__ num_blocked; int /*<<< orphan*/  max_blocked; scalar_t__ largest_known_received; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ h2o_qpack_encoder_t ;

/* Variables and functions */
 TYPE_1__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  header_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

h2o_qpack_encoder_t *h2o_qpack_create_encoder(uint32_t header_table_size, uint16_t max_blocked)
{
    h2o_qpack_encoder_t *qpack = h2o_mem_alloc(sizeof(*qpack));
    header_table_init(&qpack->table, header_table_size);
    qpack->largest_known_received = 0;
    qpack->max_blocked = max_blocked;
    qpack->num_blocked = 0;
    memset(&qpack->inflight, 0, sizeof(qpack->inflight));
    return qpack;
}