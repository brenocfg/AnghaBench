#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gfree; int /*<<< orphan*/  gmallocarray; int /*<<< orphan*/  greallocarray; int /*<<< orphan*/  grealloc; int /*<<< orphan*/  gsubstrdup; int /*<<< orphan*/  gstrndup; int /*<<< orphan*/  gstrdup; int /*<<< orphan*/  gcalloc; int /*<<< orphan*/  gmalloc; } ;
typedef  TYPE_1__ git_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  stdalloc__calloc ; 
 int /*<<< orphan*/  stdalloc__free ; 
 int /*<<< orphan*/  stdalloc__malloc ; 
 int /*<<< orphan*/  stdalloc__mallocarray ; 
 int /*<<< orphan*/  stdalloc__realloc ; 
 int /*<<< orphan*/  stdalloc__reallocarray ; 
 int /*<<< orphan*/  stdalloc__strdup ; 
 int /*<<< orphan*/  stdalloc__strndup ; 
 int /*<<< orphan*/  stdalloc__substrdup ; 

int git_stdalloc_init_allocator(git_allocator *allocator)
{
	allocator->gmalloc = stdalloc__malloc;
	allocator->gcalloc = stdalloc__calloc;
	allocator->gstrdup = stdalloc__strdup;
	allocator->gstrndup = stdalloc__strndup;
	allocator->gsubstrdup = stdalloc__substrdup;
	allocator->grealloc = stdalloc__realloc;
	allocator->greallocarray = stdalloc__reallocarray;
	allocator->gmallocarray = stdalloc__mallocarray;
	allocator->gfree = stdalloc__free;
	return 0;
}