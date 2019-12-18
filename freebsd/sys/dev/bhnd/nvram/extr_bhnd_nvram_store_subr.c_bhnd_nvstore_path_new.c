#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* path_str; int /*<<< orphan*/ * pending; scalar_t__ num_vars; int /*<<< orphan*/ * index; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nv_free (TYPE_1__*) ; 
 TYPE_1__* bhnd_nv_malloc (int) ; 
 TYPE_1__* bhnd_nv_strndup (char const*,size_t) ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_new () ; 
 int /*<<< orphan*/  bhnd_nvram_plist_release (int /*<<< orphan*/ *) ; 

bhnd_nvstore_path *
bhnd_nvstore_path_new(const char *path_str, size_t path_len)
{
	bhnd_nvstore_path *path;

	/* Allocate new entry */
	path = bhnd_nv_malloc(sizeof(*path));
	if (path == NULL)
		return (NULL);

	path->index = NULL;
	path->num_vars = 0;

	path->pending = bhnd_nvram_plist_new();
	if (path->pending == NULL)
		goto failed;

	path->path_str = bhnd_nv_strndup(path_str, path_len);
	if (path->path_str == NULL)
		goto failed;

	return (path);

failed:
	if (path->pending != NULL)
		bhnd_nvram_plist_release(path->pending);

	if (path->path_str != NULL)
		bhnd_nv_free(path->path_str);

	bhnd_nv_free(path);

	return (NULL);
}