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
struct TYPE_3__ {size_t children_count; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ IjkMediaMeta ;

/* Variables and functions */

size_t ijkmeta_get_children_count_l(IjkMediaMeta *meta)
{
    if (!meta || !meta->children)
        return 0;

    return meta->children_count;
}