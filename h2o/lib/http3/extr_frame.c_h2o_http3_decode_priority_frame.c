#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int type; int /*<<< orphan*/  id_; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  id_; } ;
struct TYPE_7__ {int exclusive; int /*<<< orphan*/  weight_m1; TYPE_2__ dependency; TYPE_1__ prioritized; } ;
typedef  TYPE_3__ h2o_http3_priority_frame_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_FRAME ; 
 int H2O_HTTP3_PRIORITY_ELEMENT_TYPE_ROOT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  quicly_decodev (int const**,int const*) ; 

int h2o_http3_decode_priority_frame(h2o_http3_priority_frame_t *frame, const uint8_t *payload, size_t len, const char **err_desc)
{
    const uint8_t *src = payload, *end = src + len;

    if (end - src < 2)
        goto Fail;

    if ((*src & 0x7) != 0)
        goto Fail;
    frame->prioritized.type = (*src >> 6) & 0x3;
    frame->dependency.type = (*src >> 4) & 0x3;
    frame->exclusive = (*src & 0x8) != 0;
    ++src;
    if (frame->prioritized.type == H2O_HTTP3_PRIORITY_ELEMENT_TYPE_ROOT)
        goto Fail;
    if ((frame->prioritized.id_ = quicly_decodev(&src, end)) == UINT64_MAX)
        goto Fail;
    frame->dependency.id_ = 0;
    if (frame->dependency.type != H2O_HTTP3_PRIORITY_ELEMENT_TYPE_ROOT)
        if ((frame->dependency.id_ = quicly_decodev(&src, end)) == UINT64_MAX)
            goto Fail;
    if (end - src != 1)
        goto Fail;
    frame->weight_m1 = *src++;

    return 0;
Fail:
    *err_desc = "invalid PRIORITY frame";
    return H2O_HTTP3_ERROR_FRAME;
}