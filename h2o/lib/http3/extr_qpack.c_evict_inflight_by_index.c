#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_4__* entries; } ;
struct TYPE_9__ {TYPE_3__ inflight; int /*<<< orphan*/  num_blocked; } ;
typedef  TYPE_2__ h2o_qpack_encoder_t ;
struct TYPE_8__ {scalar_t__ is_blocking; } ;
struct TYPE_11__ {TYPE_1__ encoder_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void evict_inflight_by_index(h2o_qpack_encoder_t *qpack, size_t index)
{
    if (qpack->inflight.entries[index].encoder_flags.is_blocking)
        --qpack->num_blocked;
    --qpack->inflight.size;

    if (qpack->inflight.size == 0) {
        free(qpack->inflight.entries);
        memset(&qpack->inflight, 0, sizeof(qpack->inflight));
    } else if (index < qpack->inflight.size) {
        memmove(qpack->inflight.entries + index, qpack->inflight.entries + index + 1, qpack->inflight.size - index);
    }
}