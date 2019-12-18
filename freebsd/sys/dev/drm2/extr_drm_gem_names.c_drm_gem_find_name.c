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
typedef  scalar_t__ uint32_t ;
struct drm_gem_ptr_match_arg {scalar_t__ res; void* ptr; } ;
struct drm_gem_names {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_names_foreach (struct drm_gem_names*,int /*<<< orphan*/ ,struct drm_gem_ptr_match_arg*) ; 
 int /*<<< orphan*/  drm_gem_ptr_match ; 

uint32_t
drm_gem_find_name(struct drm_gem_names *names, void *ptr)
{
	struct drm_gem_ptr_match_arg arg;

	arg.res = 0;
	arg.ptr = ptr;
	drm_gem_names_foreach(names, drm_gem_ptr_match, &arg);
	return (arg.res);
}