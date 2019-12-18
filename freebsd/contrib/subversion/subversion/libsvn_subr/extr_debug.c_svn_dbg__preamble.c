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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* debug_file ; 
 long debug_line ; 
 int /*<<< orphan*/ * debug_output ; 
 int /*<<< orphan*/  quiet_mode () ; 
 char* strrchr (char const*,char) ; 

void
svn_dbg__preamble(const char *file, long line, FILE *output)
{
  debug_output = output;

  if (output != NULL && !quiet_mode())
    {
      /* Quick and dirty basename() code.  */
      const char *slash = strrchr(file, '/');

      if (slash == NULL)
        slash = strrchr(file, '\\');
      if (slash)
        debug_file = slash + 1;
      else
        debug_file = file;
    }
  debug_line = line;
}