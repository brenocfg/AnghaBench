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
struct ui_file {int dummy; } ;
struct tui_stream {int /*<<< orphan*/ * ts_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ui_file_data (struct ui_file*,struct tui_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_flush (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_fputs (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_isatty (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_put (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ui_file_rewind (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_file_delete ; 
 int /*<<< orphan*/  tui_file_flush ; 
 int /*<<< orphan*/  tui_file_fputs ; 
 int /*<<< orphan*/  tui_file_isatty ; 
 int /*<<< orphan*/  tui_file_magic ; 
 int /*<<< orphan*/  tui_file_put ; 
 int /*<<< orphan*/  tui_file_rewind ; 
 struct ui_file* ui_file_new () ; 
 struct tui_stream* xmalloc (int) ; 

__attribute__((used)) static struct ui_file *
tui_file_new (void)
{
  struct tui_stream *tui = xmalloc (sizeof (struct tui_stream));
  struct ui_file *file = ui_file_new ();
  set_ui_file_data (file, tui, tui_file_delete);
  set_ui_file_flush (file, tui_file_flush);
  set_ui_file_fputs (file, tui_file_fputs);
  set_ui_file_isatty (file, tui_file_isatty);
  set_ui_file_rewind (file, tui_file_rewind);
  set_ui_file_put (file, tui_file_put);
  tui->ts_magic = &tui_file_magic;
  return file;
}