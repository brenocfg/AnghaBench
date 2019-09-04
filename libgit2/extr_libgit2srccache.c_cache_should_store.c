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
typedef  size_t git_object_t ;

/* Variables and functions */
 scalar_t__ git_cache__enabled ; 
 size_t* git_cache__max_object_size ; 

__attribute__((used)) static bool cache_should_store(git_object_t object_type, size_t object_size)
{
	size_t max_size = git_cache__max_object_size[object_type];
	return git_cache__enabled && object_size < max_size;
}