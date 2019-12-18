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
struct ui_file {int /*<<< orphan*/ * magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_file_delete ; 
 int /*<<< orphan*/  null_file_flush ; 
 int /*<<< orphan*/  null_file_fputs ; 
 int /*<<< orphan*/  null_file_isatty ; 
 int /*<<< orphan*/  null_file_put ; 
 int /*<<< orphan*/  null_file_read ; 
 int /*<<< orphan*/  null_file_rewind ; 
 int /*<<< orphan*/  null_file_write ; 
 int /*<<< orphan*/  set_ui_file_data (struct ui_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_flush (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_fputs (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_isatty (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_put (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_read (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_rewind (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_write (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_file_magic ; 
 struct ui_file* xmalloc (int) ; 

struct ui_file *
ui_file_new (void)
{
  struct ui_file *file = xmalloc (sizeof (struct ui_file));
  file->magic = &ui_file_magic;
  set_ui_file_data (file, NULL, null_file_delete);
  set_ui_file_flush (file, null_file_flush);
  set_ui_file_write (file, null_file_write);
  set_ui_file_fputs (file, null_file_fputs);
  set_ui_file_read (file, null_file_read);
  set_ui_file_isatty (file, null_file_isatty);
  set_ui_file_rewind (file, null_file_rewind);
  set_ui_file_put (file, null_file_put);
  return file;
}