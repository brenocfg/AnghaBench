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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,struct ui_file*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xvasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

void
vfprintf_unfiltered (struct ui_file *stream, const char *format, va_list args)
{
  char *linebuffer;
  struct cleanup *old_cleanups;

  xvasprintf (&linebuffer, format, args);
  old_cleanups = make_cleanup (xfree, linebuffer);
  fputs_unfiltered (linebuffer, stream);
  do_cleanups (old_cleanups);
}