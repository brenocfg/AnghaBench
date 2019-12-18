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
 int force_update ; 
 int /*<<< orphan*/  option_date_format (char const*) ; 
 int /*<<< orphan*/  option_export_marks (char const*) ; 
 int /*<<< orphan*/  option_import_marks (char const*,int,int) ; 
 int relative_marks_paths ; 
 int require_explicit_termination ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_one_feature(const char *feature, int from_stream)
{
	const char *arg;

	if (skip_prefix(feature, "date-format=", &arg)) {
		option_date_format(arg);
	} else if (skip_prefix(feature, "import-marks=", &arg)) {
		option_import_marks(arg, from_stream, 0);
	} else if (skip_prefix(feature, "import-marks-if-exists=", &arg)) {
		option_import_marks(arg, from_stream, 1);
	} else if (skip_prefix(feature, "export-marks=", &arg)) {
		option_export_marks(arg);
	} else if (!strcmp(feature, "alias")) {
		; /* Don't die - this feature is supported */
	} else if (!strcmp(feature, "get-mark")) {
		; /* Don't die - this feature is supported */
	} else if (!strcmp(feature, "cat-blob")) {
		; /* Don't die - this feature is supported */
	} else if (!strcmp(feature, "relative-marks")) {
		relative_marks_paths = 1;
	} else if (!strcmp(feature, "no-relative-marks")) {
		relative_marks_paths = 0;
	} else if (!strcmp(feature, "done")) {
		require_explicit_termination = 1;
	} else if (!strcmp(feature, "force")) {
		force_update = 1;
	} else if (!strcmp(feature, "notes") || !strcmp(feature, "ls")) {
		; /* do nothing; we have the feature */
	} else {
		return 0;
	}

	return 1;
}