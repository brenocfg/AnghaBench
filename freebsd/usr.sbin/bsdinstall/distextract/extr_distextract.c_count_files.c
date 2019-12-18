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
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  errormsg ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 scalar_t__ EINVAL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * archive ; 
 char* archive_error_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_read_new () ; 
 int archive_read_next_header (int /*<<< orphan*/ *,struct archive_entry**) ; 
 int archive_read_open_filename (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_format_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dialog_msgbox (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* distdir ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
count_files(const char *file)
{
	static FILE *manifest = NULL;
	char *p;
	int file_count;
	int retval;
	size_t span;
	struct archive_entry *entry;
	char line[512];
	char path[PATH_MAX];
	char errormsg[PATH_MAX + 512];

	if (manifest == NULL) {
		snprintf(path, sizeof(path), "%s/MANIFEST", distdir);
		manifest = fopen(path, "r");
	}

	if (manifest != NULL) {
		rewind(manifest);
		while (fgets(line, sizeof(line), manifest) != NULL) {
			p = &line[0];
			span = strcspn(p, "\t") ;
			if (span < 1 || strncmp(p, file, span) != 0)
				continue;

			/*
			 * We're at the right manifest line. The file count is
			 * in the third element
			 */
			span = strcspn(p += span + (*p != '\0' ? 1 : 0), "\t");
			span = strcspn(p += span + (*p != '\0' ? 1 : 0), "\t");
			if (span > 0) {
				file_count = (int)strtol(p, (char **)NULL, 10);
				if (file_count == 0 && errno == EINVAL)
					continue;
				return (file_count);
			}
		}
	}

	/*
	 * Either no manifest, or manifest didn't mention this archive.
	 * Use archive(3) to read the archive, counting files within.
	 */
	if ((archive = archive_read_new()) == NULL) {
		snprintf(errormsg, sizeof(errormsg),
		    "Error: %s\n", archive_error_string(NULL));
		dialog_msgbox("Extract Error", errormsg, 0, 0, TRUE);
		return (-1);
	}
	archive_read_support_format_all(archive);
	archive_read_support_filter_all(archive);
	snprintf(path, sizeof(path), "%s/%s", distdir, file);
	retval = archive_read_open_filename(archive, path, 4096);
	if (retval != ARCHIVE_OK) {
		snprintf(errormsg, sizeof(errormsg),
		    "Error while extracting %s: %s\n", file,
		    archive_error_string(archive));
		dialog_msgbox("Extract Error", errormsg, 0, 0, TRUE);
		archive = NULL;
		return (-1);
	}

	file_count = 0;
	while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
		file_count++;
	archive_read_free(archive);
	archive = NULL;

	return (file_count);
}