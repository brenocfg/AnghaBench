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
typedef  int /*<<< orphan*/  va_list ;
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error_stream (struct ui_file*) ; 
 int /*<<< orphan*/  make_cleanup_ui_file_delete (struct ui_file*) ; 
 struct ui_file* mem_fileopen () ; 
 int /*<<< orphan*/  vfprintf_unfiltered (struct ui_file*,char const*,int /*<<< orphan*/ ) ; 

void
verror (const char *string, va_list args)
{
  struct ui_file *tmp_stream = mem_fileopen ();
  make_cleanup_ui_file_delete (tmp_stream);
  vfprintf_unfiltered (tmp_stream, string, args);
  error_stream (tmp_stream);
}