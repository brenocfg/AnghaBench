#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zwp_primary_selection_source_v1 {int dummy; } ;
struct TYPE_3__ {struct zwp_primary_selection_source_v1* dataSourceForPrimarySelection; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  zwp_primary_selection_source_v1_destroy (struct zwp_primary_selection_source_v1*) ; 

__attribute__((used)) static void primary_selection_source_canceled(void *data, struct zwp_primary_selection_source_v1 *primary_selection_source) {
    if (_glfw.wl.dataSourceForPrimarySelection == primary_selection_source)
        _glfw.wl.dataSourceForPrimarySelection = NULL;
    zwp_primary_selection_source_v1_destroy(primary_selection_source);
}