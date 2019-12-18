#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int click_events_init; } ;

/* Variables and functions */
 TYPE_1__ child ; 
 int /*<<< orphan*/  child_write_output () ; 
 int /*<<< orphan*/  gen ; 
 int /*<<< orphan*/  yajl_gen_array_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void child_click_events_initialize(void) {
    if (!child.click_events_init) {
        yajl_gen_array_open(gen);
        child_write_output();
        child.click_events_init = true;
    }
}