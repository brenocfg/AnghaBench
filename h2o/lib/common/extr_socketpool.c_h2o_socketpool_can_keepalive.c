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
struct TYPE_3__ {scalar_t__ timeout; } ;
typedef  TYPE_1__ h2o_socketpool_t ;

/* Variables and functions */

int h2o_socketpool_can_keepalive(h2o_socketpool_t *pool)
{
    return pool->timeout > 0;
}