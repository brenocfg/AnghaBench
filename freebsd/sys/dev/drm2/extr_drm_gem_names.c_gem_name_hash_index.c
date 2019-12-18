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
struct drm_gem_names_head {int dummy; } ;
struct drm_gem_names {int hash_mask; struct drm_gem_names_head* names_hash; } ;

/* Variables and functions */

__attribute__((used)) static struct drm_gem_names_head *
gem_name_hash_index(struct drm_gem_names *names, int name)
{

	return (&names->names_hash[name & names->hash_mask]);
}