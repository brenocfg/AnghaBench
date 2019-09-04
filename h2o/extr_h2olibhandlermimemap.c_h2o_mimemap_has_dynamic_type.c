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
struct TYPE_3__ {scalar_t__ num_dynamic; } ;
typedef  TYPE_1__ h2o_mimemap_t ;

/* Variables and functions */

int h2o_mimemap_has_dynamic_type(h2o_mimemap_t *mimemap)
{
    return mimemap->num_dynamic != 0;
}