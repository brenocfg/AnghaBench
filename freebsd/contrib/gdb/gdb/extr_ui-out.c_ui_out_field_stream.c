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
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct ui_out {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ui_file_rewind (int /*<<< orphan*/ ) ; 
 char* ui_file_xstrdup (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  ui_out_field_skip (struct ui_out*,char const*) ; 
 int /*<<< orphan*/  ui_out_field_string (struct ui_out*,char const*,char*) ; 
 int /*<<< orphan*/  xfree ; 

void
ui_out_field_stream (struct ui_out *uiout,
		     const char *fldname,
		     struct ui_stream *buf)
{
  long length;
  char *buffer = ui_file_xstrdup (buf->stream, &length);
  struct cleanup *old_cleanup = make_cleanup (xfree, buffer);
  if (length > 0)
    ui_out_field_string (uiout, fldname, buffer);
  else
    ui_out_field_skip (uiout, fldname);
  ui_file_rewind (buf->stream);
  do_cleanups (old_cleanup);
}