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
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  print_address_symbolic (int /*<<< orphan*/ ,struct ui_file*,int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* tui_file_get_strbuf (struct ui_file*) ; 
 struct ui_file* tui_sfileopen (int) ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 

__attribute__((used)) static char*
tui_get_function_from_frame (struct frame_info *fi)
{
  static char name[256];
  struct ui_file *stream = tui_sfileopen (256);
  char *p;

  print_address_symbolic (get_frame_pc (fi), stream, demangle, "");
  p = tui_file_get_strbuf (stream);

  /* Use simple heuristics to isolate the function name.  The symbol can
     be demangled and we can have function parameters.  Remove them because
     the status line is too short to display them.  */
  if (*p == '<')
    p++;
  strncpy (name, p, sizeof (name));
  p = strchr (name, '(');
  if (!p)
    p = strchr (name, '>');
  if (p)
    *p = 0;
  p = strchr (name, '+');
  if (p)
    *p = 0;
  ui_file_delete (stream);
  return name;
}