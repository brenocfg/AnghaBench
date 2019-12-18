#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int parsing_bindings ; 
 int parsing_tray_outputs ; 

__attribute__((used)) static int config_end_array_cb(void *params_) {
    parsing_bindings = false;
    parsing_tray_outputs = false;
    return 1;
}