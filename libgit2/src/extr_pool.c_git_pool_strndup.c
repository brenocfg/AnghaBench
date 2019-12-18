#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int item_size; } ;
typedef  TYPE_1__ git_pool ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* git_pool_malloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

char *git_pool_strndup(git_pool *pool, const char *str, size_t n)
{
	char *ptr = NULL;

	assert(pool && str && pool->item_size == sizeof(char));

	if (n == SIZE_MAX)
		return NULL;

	if ((ptr = git_pool_malloc(pool, (n + 1))) != NULL) {
		memcpy(ptr, str, n);
		ptr[n] = '\0';
	}

	return ptr;
}