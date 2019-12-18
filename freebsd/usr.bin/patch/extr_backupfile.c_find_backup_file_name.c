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

/* Variables and functions */
 scalar_t__ backup_type ; 
 char const* basename (char*) ; 
 char* concat (char const*,char*) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* make_version_name (char const*,int) ; 
 int max_backup_version (char*,char*) ; 
 scalar_t__ numbered_existing ; 
 scalar_t__ simple ; 
 char* simple_backup_suffix ; 
 char* strdup (char const*) ; 

char *
find_backup_file_name(const char *file)
{
	char	*dir, *base_versions, *tmp_file;
	int	highest_backup;

	if (backup_type == simple)
		return concat(file, simple_backup_suffix);
	tmp_file = strdup(file);
	if (tmp_file == NULL)
		return NULL;
	base_versions = concat(basename(tmp_file), ".~");
	free(tmp_file);
	if (base_versions == NULL)
		return NULL;
	tmp_file = strdup(file);
	if (tmp_file == NULL) {
		free(base_versions);
		return NULL;
	}
	dir = dirname(tmp_file);
	if (dir == NULL) {
		free(base_versions);
		free(tmp_file);
		return NULL;
	}
	highest_backup = max_backup_version(base_versions, dir);
	free(base_versions);
	free(tmp_file);
	if (backup_type == numbered_existing && highest_backup == 0)
		return concat(file, simple_backup_suffix);
	return make_version_name(file, highest_backup + 1);
}