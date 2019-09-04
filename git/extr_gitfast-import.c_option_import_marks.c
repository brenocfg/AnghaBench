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
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ import_marks_file ; 
 int import_marks_file_from_stream ; 
 int import_marks_file_ignore_missing ; 
 scalar_t__ make_fast_import_path (char const*) ; 
 int /*<<< orphan*/  read_marks () ; 
 int /*<<< orphan*/  safe_create_leading_directories_const (scalar_t__) ; 

__attribute__((used)) static void option_import_marks(const char *marks,
					int from_stream, int ignore_missing)
{
	if (import_marks_file) {
		if (from_stream)
			die("Only one import-marks command allowed per stream");

		/* read previous mark file */
		if(!import_marks_file_from_stream)
			read_marks();
	}

	import_marks_file = make_fast_import_path(marks);
	safe_create_leading_directories_const(import_marks_file);
	import_marks_file_from_stream = from_stream;
	import_marks_file_ignore_missing = ignore_missing;
}