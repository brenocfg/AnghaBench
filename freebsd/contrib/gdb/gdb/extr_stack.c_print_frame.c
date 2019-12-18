#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct symtab_and_line {scalar_t__ pc; TYPE_1__* symtab; int /*<<< orphan*/  line; } ;
struct symbol {int dummy; } ;
struct print_args_args {int /*<<< orphan*/  stream; struct symbol* func; struct frame_info* fi; } ;
typedef  struct symbol minimal_symbol ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum language { ____Placeholder_language } language ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  DMGL_ANSI ; 
 int LOC_AND_ADDRESS ; 
 char* PC_SOLIB (scalar_t__) ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int SYMBOL_LANGUAGE (struct symbol*) ; 
 char* SYMBOL_PRINT_NAME (struct symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 scalar_t__ addressprint ; 
 int /*<<< orphan*/  annotate_frame_address () ; 
 int /*<<< orphan*/  annotate_frame_address_end () ; 
 int /*<<< orphan*/  annotate_frame_args () ; 
 int /*<<< orphan*/  annotate_frame_begin (int,scalar_t__) ; 
 int /*<<< orphan*/  annotate_frame_function_name () ; 
 int /*<<< orphan*/  annotate_frame_source_begin () ; 
 int /*<<< orphan*/  annotate_frame_source_end () ; 
 int /*<<< orphan*/  annotate_frame_source_file () ; 
 int /*<<< orphan*/  annotate_frame_source_file_end () ; 
 int /*<<< orphan*/  annotate_frame_source_line () ; 
 int /*<<< orphan*/  annotate_frame_where () ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,struct print_args_args*,char*,int /*<<< orphan*/ ) ; 
 char* cplus_demangle (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct symbol* find_pc_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_symbol_filtered (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_frame_address_in_block (struct frame_info*) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 int language_cplus ; 
 int language_unknown ; 
 struct symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_stream_delete (struct ui_stream*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_args_stub ; 
 int /*<<< orphan*/  ui_left ; 
 int /*<<< orphan*/  ui_out_field_core_addr (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ui_out_field_fmt_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ui_out_wrap_hint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
print_frame (struct frame_info *fi, 
	     int level, 
	     int source, 
	     int args, 
	     struct symtab_and_line sal)
{
  struct symbol *func;
  char *funname = 0;
  enum language funlang = language_unknown;
  struct ui_stream *stb;
  struct cleanup *old_chain;
  struct cleanup *list_chain;

  stb = ui_out_stream_new (uiout);
  old_chain = make_cleanup_ui_out_stream_delete (stb);

  func = find_pc_function (get_frame_address_in_block (fi));
  if (func)
    {
      /* In certain pathological cases, the symtabs give the wrong
         function (when we are in the first function in a file which
         is compiled without debugging symbols, the previous function
         is compiled with debugging symbols, and the "foo.o" symbol
         that is supposed to tell us where the file with debugging symbols
         ends has been truncated by ar because it is longer than 15
         characters).  This also occurs if the user uses asm() to create
         a function but not stabs for it (in a file compiled -g).

         So look in the minimal symbol tables as well, and if it comes
         up with a larger address for the function use that instead.
         I don't think this can ever cause any problems; there shouldn't
         be any minimal symbols in the middle of a function; if this is
         ever changed many parts of GDB will need to be changed (and we'll
         create a find_pc_minimal_function or some such).  */

      struct minimal_symbol *msymbol = lookup_minimal_symbol_by_pc (get_frame_address_in_block (fi));
      if (msymbol != NULL
	  && (SYMBOL_VALUE_ADDRESS (msymbol)
	      > BLOCK_START (SYMBOL_BLOCK_VALUE (func))))
	{
#if 0
	  /* There is no particular reason to think the line number
	     information is wrong.  Someone might have just put in
	     a label with asm() but left the line numbers alone.  */
	  /* In this case we have no way of knowing the source file
	     and line number, so don't print them.  */
	  sal.symtab = 0;
#endif
	  /* We also don't know anything about the function besides
	     its address and name.  */
	  func = 0;
	  funname = DEPRECATED_SYMBOL_NAME (msymbol);
	  funlang = SYMBOL_LANGUAGE (msymbol);
	}
      else
	{
	  /* I'd like to use SYMBOL_PRINT_NAME() here, to display the
	     demangled name that we already have stored in the symbol
	     table, but we stored a version with DMGL_PARAMS turned
	     on, and here we don't want to display parameters. So call
	     the demangler again, with DMGL_ANSI only. (Yes, I know
	     that printf_symbol_filtered() will again try to demangle
	     the name on the fly, but the issue is that if
	     cplus_demangle() fails here, it'll fail there too. So we
	     want to catch the failure ("demangled==NULL" case below)
	     here, while we still have our hands on the function
	     symbol.) */
	  char *demangled;
	  funname = DEPRECATED_SYMBOL_NAME (func);
	  funlang = SYMBOL_LANGUAGE (func);
	  if (funlang == language_cplus)
	    {
	      demangled = cplus_demangle (funname, DMGL_ANSI);
	      if (demangled == NULL)
		/* If the demangler fails, try the demangled name from
		   the symbol table. This'll have parameters, but
		   that's preferable to diplaying a mangled name. */
		funname = SYMBOL_PRINT_NAME (func);
	    }
	}
    }
  else
    {
      struct minimal_symbol *msymbol = lookup_minimal_symbol_by_pc (get_frame_address_in_block (fi));
      if (msymbol != NULL)
	{
	  funname = DEPRECATED_SYMBOL_NAME (msymbol);
	  funlang = SYMBOL_LANGUAGE (msymbol);
	}
    }

  annotate_frame_begin (level == -1 ? 0 : level, get_frame_pc (fi));

  list_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "frame");

  if (level >= 0)
    {
      ui_out_text (uiout, "#");
      ui_out_field_fmt_int (uiout, 2, ui_left, "level", level);
    }
  if (addressprint)
    if (get_frame_pc (fi) != sal.pc
	|| !sal.symtab
	|| source == LOC_AND_ADDRESS)
      {
	annotate_frame_address ();
	ui_out_field_core_addr (uiout, "addr", get_frame_pc (fi));
	annotate_frame_address_end ();
	ui_out_text (uiout, " in ");
      }
  annotate_frame_function_name ();
  fprintf_symbol_filtered (stb->stream, funname ? funname : "??", funlang,
			   DMGL_ANSI);
  ui_out_field_stream (uiout, "func", stb);
  ui_out_wrap_hint (uiout, "   ");
  annotate_frame_args ();
      
  ui_out_text (uiout, " (");
  if (args)
    {
      struct print_args_args args;
      struct cleanup *args_list_chain;
      args.fi = fi;
      args.func = func;
      args.stream = gdb_stdout;
      args_list_chain = make_cleanup_ui_out_list_begin_end (uiout, "args");
      catch_errors (print_args_stub, &args, "", RETURN_MASK_ALL);
      /* FIXME: args must be a list. If one argument is a string it will
		 have " that will not be properly escaped.  */
      /* Invoke ui_out_tuple_end.  */
      do_cleanups (args_list_chain);
      QUIT;
    }
  ui_out_text (uiout, ")");
  if (sal.symtab && sal.symtab->filename)
    {
      annotate_frame_source_begin ();
      ui_out_wrap_hint (uiout, "   ");
      ui_out_text (uiout, " at ");
      annotate_frame_source_file ();
      ui_out_field_string (uiout, "file", sal.symtab->filename);
      annotate_frame_source_file_end ();
      ui_out_text (uiout, ":");
      annotate_frame_source_line ();
      ui_out_field_int (uiout, "line", sal.line);
      annotate_frame_source_end ();
    }

#ifdef PC_SOLIB
  if (!funname || (!sal.symtab || !sal.symtab->filename))
    {
      char *lib = PC_SOLIB (get_frame_pc (fi));
      if (lib)
	{
	  annotate_frame_where ();
	  ui_out_wrap_hint (uiout, "  ");
	  ui_out_text (uiout, " from ");
	  ui_out_field_string (uiout, "from", lib);
	}
    }
#endif /* PC_SOLIB */

  /* do_cleanups will call ui_out_tuple_end() for us.  */
  do_cleanups (list_chain);
  ui_out_text (uiout, "\n");
  do_cleanups (old_chain);
}