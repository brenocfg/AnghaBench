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
struct TYPE_4__ {TYPE_2__* prefilters; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_5__ {scalar_t__ on_setup_ostream; struct TYPE_5__* next; } ;
typedef  TYPE_2__ h2o_req_prefilter_t ;

/* Variables and functions */
 scalar_t__ on_prefilter_setup_stream ; 

__attribute__((used)) static int prefilter_is_registered(h2o_req_t *req)
{
    h2o_req_prefilter_t *prefilter;
    for (prefilter = req->prefilters; prefilter != NULL; prefilter = prefilter->next)
        if (prefilter->on_setup_ostream == on_prefilter_setup_stream)
            return 1;
    return 0;
}