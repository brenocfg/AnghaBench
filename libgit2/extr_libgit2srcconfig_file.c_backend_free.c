#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_4__ {int /*<<< orphan*/  values_mutex; int /*<<< orphan*/  entries; } ;
struct TYPE_5__ {TYPE_1__ header; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mutex_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void backend_free(git_config_backend *_backend)
{
	diskfile_backend *backend = (diskfile_backend *)_backend;

	if (backend == NULL)
		return;

	config_file_clear(&backend->file);
	git_config_entries_free(backend->header.entries);
	git_mutex_free(&backend->header.values_mutex);
	git__free(backend);
}