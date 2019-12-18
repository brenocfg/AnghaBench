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
struct symtab_and_line {scalar_t__ pc; scalar_t__ line; scalar_t__ symtab; } ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUMMY_FRAME ; 
 int LOCATION ; 
 int LOC_AND_ADDRESS ; 
 scalar_t__ SIGTRAMP_FRAME ; 
 int SRC_AND_LOC ; 
 int SRC_LINE ; 
 scalar_t__ addressprint ; 
 int /*<<< orphan*/  annotate_frame_address () ; 
 int /*<<< orphan*/  annotate_frame_address_end () ; 
 int /*<<< orphan*/  annotate_frame_begin (int,scalar_t__) ; 
 int /*<<< orphan*/  annotate_frame_end () ; 
 int /*<<< orphan*/  annotate_function_call () ; 
 int /*<<< orphan*/  annotate_signal_handler_caller () ; 
 scalar_t__ annotation_level ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  find_frame_sal (struct frame_info*,struct symtab_and_line*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 int get_lines_to_list () ; 
 int identify_source_line (scalar_t__,scalar_t__,int,scalar_t__) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ max (scalar_t__,int) ; 
 int /*<<< orphan*/  print_frame (struct frame_info*,int,int,int,struct symtab_and_line) ; 
 int /*<<< orphan*/  print_frame_info_listing_hook (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_source_lines (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_source_symtab_and_line (struct symtab_and_line*) ; 
 int /*<<< orphan*/  set_default_breakpoint (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_default_source_symtab_and_line () ; 
 int /*<<< orphan*/  ui_left ; 
 int /*<<< orphan*/  ui_out_field_core_addr (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ui_out_field_fmt_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ui_out_is_mi_like_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

void
print_frame_info (struct frame_info *fi, int level, int source, int args)
{
  struct symtab_and_line sal;
  int source_print;
  int location_print;

  if (get_frame_type (fi) == DUMMY_FRAME
      || get_frame_type (fi) == SIGTRAMP_FRAME)
    {
      struct cleanup *uiout_cleanup
	= make_cleanup_ui_out_tuple_begin_end (uiout, "frame");

      annotate_frame_begin (level == -1 ? 0 : level, get_frame_pc (fi));

      /* Do this regardless of SOURCE because we don't have any source
         to list for this frame.  */
      if (level >= 0)
        {
          ui_out_text (uiout, "#");
          ui_out_field_fmt_int (uiout, 2, ui_left, "level", level);
        }
      if (ui_out_is_mi_like_p (uiout))
        {
          annotate_frame_address ();
          ui_out_field_core_addr (uiout, "addr", get_frame_pc (fi));
          annotate_frame_address_end ();
        }

      if (get_frame_type (fi) == DUMMY_FRAME)
        {
          annotate_function_call ();
          ui_out_field_string (uiout, "func", "<function called from gdb>");
	}
      else if (get_frame_type (fi) == SIGTRAMP_FRAME)
        {
	  annotate_signal_handler_caller ();
          ui_out_field_string (uiout, "func", "<signal handler called>");
        }
      ui_out_text (uiout, "\n");
      annotate_frame_end ();

      do_cleanups (uiout_cleanup);
      return;
    }

  /* If fi is not the innermost frame, that normally means that fi->pc
     points to *after* the call instruction, and we want to get the
     line containing the call, never the next line.  But if the next
     frame is a SIGTRAMP_FRAME or a DUMMY_FRAME, then the next frame
     was not entered as the result of a call, and we want to get the
     line containing fi->pc.  */
  find_frame_sal (fi, &sal);

  location_print = (source == LOCATION 
		    || source == LOC_AND_ADDRESS
		    || source == SRC_AND_LOC);

  if (location_print || !sal.symtab)
    print_frame (fi, level, source, args, sal);

  source_print = (source == SRC_LINE || source == SRC_AND_LOC);

  if (sal.symtab)
    set_current_source_symtab_and_line (&sal);

  if (source_print && sal.symtab)
    {
      struct symtab_and_line cursal;
      int done = 0;
      int mid_statement = (source == SRC_LINE) && (get_frame_pc (fi) != sal.pc);

      if (annotation_level)
	done = identify_source_line (sal.symtab, sal.line, mid_statement,
				     get_frame_pc (fi));
      if (!done)
	{
	  if (print_frame_info_listing_hook)
	    print_frame_info_listing_hook (sal.symtab, sal.line, sal.line + 1, 0);
	  else
	    {
	      /* We used to do this earlier, but that is clearly
		 wrong. This function is used by many different
		 parts of gdb, including normal_stop in infrun.c,
		 which uses this to print out the current PC
		 when we stepi/nexti into the middle of a source
		 line. Only the command line really wants this
		 behavior. Other UIs probably would like the
		 ability to decide for themselves if it is desired. */
	      if (addressprint && mid_statement)
		{
		  ui_out_field_core_addr (uiout, "addr", get_frame_pc (fi));
		  ui_out_text (uiout, "\t");
		}

	      print_source_lines (sal.symtab, sal.line, sal.line + 1, 0);
	    }
	}
      /* Make sure we have at least a default source file */
      set_default_source_symtab_and_line ();
      cursal = get_current_source_symtab_and_line ();
      cursal.line = max (sal.line - get_lines_to_list () / 2, 1);
      set_current_source_symtab_and_line (&cursal);
    }

  if (source != 0)
    set_default_breakpoint (1, get_frame_pc (fi), sal.symtab, sal.line);

  annotate_frame_end ();

  gdb_flush (gdb_stdout);
}