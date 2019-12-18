#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {char* paths; TYPE_1__ patch; } ;
typedef  TYPE_2__ patch_generated_with_delta ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_PATCH_GENERATED_ALLOCATED ; 
 TYPE_2__* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int patch_generated_with_delta_alloc(
	patch_generated_with_delta **out,
	const char **old_path,
	const char **new_path)
{
	patch_generated_with_delta *pd;
	size_t old_len = *old_path ? strlen(*old_path) : 0;
	size_t new_len = *new_path ? strlen(*new_path) : 0;
	size_t alloc_len;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, sizeof(*pd), old_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, new_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 2);

	*out = pd = git__calloc(1, alloc_len);
	GIT_ERROR_CHECK_ALLOC(pd);

	pd->patch.flags = GIT_PATCH_GENERATED_ALLOCATED;

	if (*old_path) {
		memcpy(&pd->paths[0], *old_path, old_len);
		*old_path = &pd->paths[0];
	} else if (*new_path)
		*old_path = &pd->paths[old_len + 1];

	if (*new_path) {
		memcpy(&pd->paths[old_len + 1], *new_path, new_len);
		*new_path = &pd->paths[old_len + 1];
	} else if (*old_path)
		*new_path = &pd->paths[0];

	return 0;
}