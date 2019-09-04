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
struct wl_data_source {int dummy; } ;
struct TYPE_3__ {struct wl_data_source* dataSourceForClipboard; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  wl_data_source_destroy (struct wl_data_source*) ; 

__attribute__((used)) static void data_source_canceled(void *data, struct wl_data_source *wl_data_source) {
    if (_glfw.wl.dataSourceForClipboard == wl_data_source)
        _glfw.wl.dataSourceForClipboard = NULL;
    wl_data_source_destroy(wl_data_source);
}