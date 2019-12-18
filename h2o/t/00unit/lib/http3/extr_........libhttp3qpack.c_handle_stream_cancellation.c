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
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {size_t size; TYPE_1__* entries; } ;
struct TYPE_8__ {TYPE_2__ inflight; } ;
typedef  TYPE_3__ h2o_qpack_encoder_t ;
struct TYPE_6__ {scalar_t__ stream_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  evict_inflight_by_index (TYPE_3__*,size_t) ; 

__attribute__((used)) static int handle_stream_cancellation(h2o_qpack_encoder_t *qpack, int64_t stream_id, const char **err_desc)
{
    size_t index = 0;

    while (index < qpack->inflight.size) {
        if (qpack->inflight.entries[index].stream_id == stream_id) {
            evict_inflight_by_index(qpack, index);
        } else {
            ++index;
        }
    }

    return 0;
}