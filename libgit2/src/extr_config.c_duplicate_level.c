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
struct TYPE_2__ {scalar_t__ level; } ;
typedef  TYPE_1__ backend_internal ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int duplicate_level(void **old_raw, void *new_raw)
{
	backend_internal **old = (backend_internal **)old_raw;

	GIT_UNUSED(new_raw);

	git_error_set(GIT_ERROR_CONFIG, "there already exists a configuration for the given level (%i)", (int)(*old)->level);
	return GIT_EEXISTS;
}