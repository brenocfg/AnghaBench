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
typedef  int /*<<< orphan*/  fb_render_func_t ;
struct TYPE_2__ {void* fb_arg; int /*<<< orphan*/  fb_render_cb; } ;

/* Variables and functions */
 TYPE_1__ console ; 

void
console_fb_register(fb_render_func_t render_cb, void *arg)
{
	console.fb_render_cb = render_cb;
	console.fb_arg = arg;
}