#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* entries; } ;
struct TYPE_7__ {TYPE_1__ list; } ;
struct TYPE_8__ {TYPE_2__ blocked_streams; int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ h2o_qpack_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  header_table_dispose (int /*<<< orphan*/ *) ; 

void h2o_qpack_destroy_decoder(h2o_qpack_decoder_t *qpack)
{
    header_table_dispose(&qpack->table);
    free(qpack->blocked_streams.list.entries);
    free(qpack);
}