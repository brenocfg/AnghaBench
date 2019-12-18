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
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_size (int /*<<< orphan*/ *,size_t) ; 
 void* pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *git_pool_malloc(git_pool *pool, size_t items)
{
	return pool_alloc(pool, alloc_size(pool, items));
}