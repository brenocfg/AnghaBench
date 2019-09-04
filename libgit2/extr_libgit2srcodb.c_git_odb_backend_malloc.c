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
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 void* git_odb_backend_data_alloc (int /*<<< orphan*/ *,size_t) ; 

void *git_odb_backend_malloc(git_odb_backend *backend, size_t len)
{
	return git_odb_backend_data_alloc(backend, len);
}