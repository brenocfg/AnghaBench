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
struct bhnd_nvstore_path {struct bhnd_nvstore_path* path_str; int /*<<< orphan*/  pending; int /*<<< orphan*/ * index; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvstore_path*) ; 
 int /*<<< orphan*/  bhnd_nvram_plist_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvstore_index_free (int /*<<< orphan*/ *) ; 

void
bhnd_nvstore_path_free(struct bhnd_nvstore_path *path)
{
	/* Free the per-path index */
	if (path->index != NULL)
		bhnd_nvstore_index_free(path->index);

	bhnd_nvram_plist_release(path->pending);
	bhnd_nv_free(path->path_str);
	bhnd_nv_free(path);
}