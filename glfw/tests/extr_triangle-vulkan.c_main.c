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
struct demo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  demo_cleanup (struct demo*) ; 
 int /*<<< orphan*/  demo_create_window (struct demo*) ; 
 int /*<<< orphan*/  demo_init (struct demo*,int const,char const**) ; 
 int /*<<< orphan*/  demo_init_vk_swapchain (struct demo*) ; 
 int /*<<< orphan*/  demo_prepare (struct demo*) ; 
 int /*<<< orphan*/  demo_run (struct demo*) ; 
 int validation_error ; 

int main(const int argc, const char *argv[]) {
    struct demo demo;

    demo_init(&demo, argc, argv);
    demo_create_window(&demo);
    demo_init_vk_swapchain(&demo);

    demo_prepare(&demo);
    demo_run(&demo);

    demo_cleanup(&demo);

    return validation_error;
}