#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  status; scalar_t__ remaining; } ;
typedef  TYPE_1__ serf_databuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 

void serf_databuf_init(serf_databuf_t *databuf)
{
    /* nothing is sitting in the buffer */
    databuf->remaining = 0;

    /* avoid thinking we have hit EOF */
    databuf->status = APR_SUCCESS;
}