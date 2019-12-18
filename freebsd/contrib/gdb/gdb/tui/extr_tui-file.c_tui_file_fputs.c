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
struct tui_stream {scalar_t__ ts_streamtype; int /*<<< orphan*/  ts_strbuf; } ;

/* Variables and functions */
 scalar_t__ astring ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tui_file_adjust_strbuf (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  tui_puts (char const*) ; 
 struct tui_stream* ui_file_data (struct ui_file*) ; 

void
tui_file_fputs (const char *linebuffer, struct ui_file *file)
{
  struct tui_stream *stream = ui_file_data (file);

  if (stream->ts_streamtype == astring)
    {
      tui_file_adjust_strbuf (strlen (linebuffer), file);
      strcat (stream->ts_strbuf, linebuffer);
    }
  else
    {
      tui_puts (linebuffer);
    }
}