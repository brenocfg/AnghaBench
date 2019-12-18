#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* entries; } ;
struct TYPE_6__ {TYPE_1__ inflight; int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ h2o_qpack_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  header_table_dispose (int /*<<< orphan*/ *) ; 

void h2o_qpack_destroy_encoder(h2o_qpack_encoder_t *qpack)
{
    header_table_dispose(&qpack->table);
    free(qpack->inflight.entries);
    free(qpack);
}