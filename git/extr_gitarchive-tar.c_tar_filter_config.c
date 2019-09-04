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
struct archiver {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  write_archive; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct archiver**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARCHIVER_REMOTE ; 
 int /*<<< orphan*/  ARCHIVER_WANT_COMPRESSION_LEVELS ; 
 int /*<<< orphan*/  alloc_tar_filters ; 
 int config_error_nonbool (char const*) ; 
 struct archiver* find_tar_filter (char const*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_bool (char const*,char const*) ; 
 scalar_t__ nr_tar_filters ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct archiver** tar_filters ; 
 int /*<<< orphan*/  write_tar_filter_archive ; 
 struct archiver* xcalloc (int,int) ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int tar_filter_config(const char *var, const char *value, void *data)
{
	struct archiver *ar;
	const char *name;
	const char *type;
	int namelen;

	if (parse_config_key(var, "tar", &name, &namelen, &type) < 0 || !name)
		return 0;

	ar = find_tar_filter(name, namelen);
	if (!ar) {
		ar = xcalloc(1, sizeof(*ar));
		ar->name = xmemdupz(name, namelen);
		ar->write_archive = write_tar_filter_archive;
		ar->flags = ARCHIVER_WANT_COMPRESSION_LEVELS;
		ALLOC_GROW(tar_filters, nr_tar_filters + 1, alloc_tar_filters);
		tar_filters[nr_tar_filters++] = ar;
	}

	if (!strcmp(type, "command")) {
		if (!value)
			return config_error_nonbool(var);
		free(ar->data);
		ar->data = xstrdup(value);
		return 0;
	}
	if (!strcmp(type, "remote")) {
		if (git_config_bool(var, value))
			ar->flags |= ARCHIVER_REMOTE;
		else
			ar->flags &= ~ARCHIVER_REMOTE;
		return 0;
	}

	return 0;
}