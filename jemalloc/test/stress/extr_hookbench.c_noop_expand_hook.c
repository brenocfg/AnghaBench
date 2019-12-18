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
typedef  int /*<<< orphan*/  hook_expand_t ;

/* Variables and functions */

__attribute__((used)) static void
noop_expand_hook(void *extra, hook_expand_t type, void *address,
    size_t old_usize, size_t new_usize, uintptr_t result_raw,
    uintptr_t args_raw[4]) {
}