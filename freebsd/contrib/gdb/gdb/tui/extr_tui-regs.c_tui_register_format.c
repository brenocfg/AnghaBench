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
struct type {int dummy; } ;
struct tui_data_element {int /*<<< orphan*/  content; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,char const*) ; 
 struct ui_file* gdb_stdout ; 
 int /*<<< orphan*/  gdbarch_print_registers_info (int /*<<< orphan*/ ,struct ui_file*,struct frame_info*,int,int) ; 
 char* gdbarch_register_name (struct gdbarch*,int) ; 
 struct type* gdbarch_register_type (struct gdbarch*,int) ; 
 int /*<<< orphan*/  get_frame_register (struct frame_info*,int,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pagination_enabled ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,float,int,struct ui_file*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 char* tui_file_get_strbuf (struct ui_file*) ; 
 int /*<<< orphan*/  tui_restore_gdbout ; 
 struct ui_file* tui_sfileopen (int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
tui_register_format (struct gdbarch *gdbarch, struct frame_info *frame,
                     struct tui_data_element *data_element, int regnum)
{
  struct ui_file *stream;
  struct ui_file *old_stdout;
  const char *name;
  struct cleanup *cleanups;
  char *p, *s;
  int pos;
  struct type *type = gdbarch_register_type (gdbarch, regnum);

  name = gdbarch_register_name (gdbarch, regnum);
  if (name == 0)
    {
      return;
    }
  
  pagination_enabled = 0;
  old_stdout = gdb_stdout;
  stream = tui_sfileopen (256);
  gdb_stdout = stream;
  cleanups = make_cleanup (tui_restore_gdbout, (void*) old_stdout);
  if (TYPE_VECTOR (type) != 0 && 0)
    {
      char buf[MAX_REGISTER_SIZE];
      int len;

      len = register_size (current_gdbarch, regnum);
      fprintf_filtered (stream, "%-14s ", name);
      get_frame_register (frame, regnum, buf);
      print_scalar_formatted (buf, type, 'f', len, stream);
    }
  else
    {
      gdbarch_print_registers_info (current_gdbarch, stream,
                                    frame, regnum, 1);
    }

  /* Save formatted output in the buffer.  */
  p = tui_file_get_strbuf (stream);

  /* Remove the possible \n.  */
  s = strrchr (p, '\n');
  if (s && s[1] == 0)
    *s = 0;

  xfree (data_element->content);
  data_element->content = xstrdup (p);
  do_cleanups (cleanups);
}