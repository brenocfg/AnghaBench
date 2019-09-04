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
struct TYPE_3__ {int /*<<< orphan*/  removes; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 char* git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 int git_vector_insert (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int checkout_queue_remove(checkout_data *data, const char *path)
{
	char *copy = git_pool_strdup(&data->pool, path);
	GIT_ERROR_CHECK_ALLOC(copy);
	return git_vector_insert(&data->removes, copy);
}