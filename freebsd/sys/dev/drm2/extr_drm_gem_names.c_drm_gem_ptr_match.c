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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_gem_ptr_match_arg {void* ptr; int /*<<< orphan*/  res; } ;

/* Variables and functions */

__attribute__((used)) static int
drm_gem_ptr_match(uint32_t name, void *ptr, void *arg)
{
	struct drm_gem_ptr_match_arg *a;

	a = arg;
	if (ptr == a->ptr) {
		a->res = name;
		return (1);
	} else
		return (0);
}