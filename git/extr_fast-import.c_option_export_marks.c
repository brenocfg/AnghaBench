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
 int /*<<< orphan*/  export_marks_file ; 
 int /*<<< orphan*/  make_fast_import_path (char const*) ; 
 int /*<<< orphan*/  safe_create_leading_directories_const (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void option_export_marks(const char *marks)
{
	export_marks_file = make_fast_import_path(marks);
	safe_create_leading_directories_const(export_marks_file);
}