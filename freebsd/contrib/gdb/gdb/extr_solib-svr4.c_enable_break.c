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
struct target_ops {int dummy; } ;
struct so_list {struct so_list* next; int /*<<< orphan*/  so_original_name; } ;
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ LM_ADDR (struct so_list*) ; 
 int /*<<< orphan*/  SEC_CODE ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 char* alloca (unsigned int) ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ bfd_lookup_symbol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 unsigned int bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** bkpt_names ; 
 scalar_t__ breakpoint_addr ; 
 int /*<<< orphan*/  create_solib_event_breakpoint (scalar_t__) ; 
 int /*<<< orphan*/ * exec_bfd ; 
 scalar_t__ exec_entry_point (int /*<<< orphan*/ *,struct target_ops*) ; 
 int /*<<< orphan*/  gnutarget ; 
 unsigned int interp_plt_sect_high ; 
 unsigned int interp_plt_sect_low ; 
 unsigned int interp_text_sect_high ; 
 unsigned int interp_text_sect_low ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ read_pc () ; 
 int /*<<< orphan*/  remove_solib_event_breakpoints () ; 
 int /*<<< orphan*/  solib_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** solib_break_names ; 
 int solib_open (char*,char**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 struct so_list* svr4_current_sos () ; 
 int /*<<< orphan*/  symfile_objfile ; 
 struct target_ops* target_bfd_reopen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_close (struct target_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static int
enable_break (void)
{
  int success = 0;

#ifdef BKPT_AT_SYMBOL

  struct minimal_symbol *msymbol;
  char **bkpt_namep;
  asection *interp_sect;

  /* First, remove all the solib event breakpoints.  Their addresses
     may have changed since the last time we ran the program.  */
  remove_solib_event_breakpoints ();

  interp_text_sect_low = interp_text_sect_high = 0;
  interp_plt_sect_low = interp_plt_sect_high = 0;

  /* Find the .interp section; if not found, warn the user and drop
     into the old breakpoint at symbol code.  */
  interp_sect = bfd_get_section_by_name (exec_bfd, ".interp");
  if (interp_sect)
    {
      unsigned int interp_sect_size;
      char *buf;
      CORE_ADDR load_addr = 0;
      int load_addr_found = 0;
      struct so_list *inferior_sos;
      bfd *tmp_bfd = NULL;
      struct target_ops *tmp_bfd_target;
      int tmp_fd = -1;
      char *tmp_pathname = NULL;
      CORE_ADDR sym_addr = 0;

      /* Read the contents of the .interp section into a local buffer;
         the contents specify the dynamic linker this program uses.  */
      interp_sect_size = bfd_section_size (exec_bfd, interp_sect);
      buf = alloca (interp_sect_size);
      bfd_get_section_contents (exec_bfd, interp_sect,
				buf, 0, interp_sect_size);

      /* Now we need to figure out where the dynamic linker was
         loaded so that we can load its symbols and place a breakpoint
         in the dynamic linker itself.

         This address is stored on the stack.  However, I've been unable
         to find any magic formula to find it for Solaris (appears to
         be trivial on GNU/Linux).  Therefore, we have to try an alternate
         mechanism to find the dynamic linker's base address.  */

      tmp_fd  = solib_open (buf, &tmp_pathname);
      if (tmp_fd >= 0)
	tmp_bfd = bfd_fdopenr (tmp_pathname, gnutarget, tmp_fd);

      if (tmp_bfd == NULL)
	goto bkpt_at_symbol;

      /* Make sure the dynamic linker's really a useful object.  */
      if (!bfd_check_format (tmp_bfd, bfd_object))
	{
	  warning ("Unable to grok dynamic linker %s as an object file", buf);
	  bfd_close (tmp_bfd);
	  goto bkpt_at_symbol;
	}

      /* Now convert the TMP_BFD into a target.  That way target, as
         well as BFD operations can be used.  Note that closing the
         target will also close the underlying bfd.  */
      tmp_bfd_target = target_bfd_reopen (tmp_bfd);

      /* If the entry in _DYNAMIC for the dynamic linker has already
         been filled in, we can read its base address from there. */
      inferior_sos = svr4_current_sos ();
      if (inferior_sos)
	{
	  /* Connected to a running target.  Update our shared library table. */
	  solib_add (NULL, 0, NULL, auto_solib_add);
	}
      while (inferior_sos)
	{
	  if (strcmp (buf, inferior_sos->so_original_name) == 0)
	    {
	      load_addr_found = 1;
	      load_addr = LM_ADDR (inferior_sos);
	      break;
	    }
	  inferior_sos = inferior_sos->next;
	}

      /* Otherwise we find the dynamic linker's base address by examining
	 the current pc (which should point at the entry point for the
	 dynamic linker) and subtracting the offset of the entry point.  */
      if (!load_addr_found)
	load_addr = (read_pc ()
		     - exec_entry_point (tmp_bfd, tmp_bfd_target));

      /* Record the relocated start and end address of the dynamic linker
         text and plt section for svr4_in_dynsym_resolve_code.  */
      interp_sect = bfd_get_section_by_name (tmp_bfd, ".text");
      if (interp_sect)
	{
	  interp_text_sect_low =
	    bfd_section_vma (tmp_bfd, interp_sect) + load_addr;
	  interp_text_sect_high =
	    interp_text_sect_low + bfd_section_size (tmp_bfd, interp_sect);
	}
      interp_sect = bfd_get_section_by_name (tmp_bfd, ".plt");
      if (interp_sect)
	{
	  interp_plt_sect_low =
	    bfd_section_vma (tmp_bfd, interp_sect) + load_addr;
	  interp_plt_sect_high =
	    interp_plt_sect_low + bfd_section_size (tmp_bfd, interp_sect);
	}

      /* Now try to set a breakpoint in the dynamic linker.  */
      for (bkpt_namep = solib_break_names; *bkpt_namep != NULL; bkpt_namep++)
	{
          /* On ABI's that use function descriptors, there are usually
             two linker symbols associated with each C function: one
             pointing at the actual entry point of the machine code,
             and one pointing at the function's descriptor.  The
             latter symbol has the same name as the C function.

             What we're looking for here is the machine code entry
             point, so we are only interested in symbols in code
             sections.  */
	  sym_addr = bfd_lookup_symbol (tmp_bfd, *bkpt_namep, SEC_CODE);
	  if (sym_addr != 0)
	    break;
	}

      /* We're done with both the temporary bfd and target.  Remember,
         closing the target closes the underlying bfd.  */
      target_close (tmp_bfd_target, 0);

      if (sym_addr != 0)
	{
	  create_solib_event_breakpoint (load_addr + sym_addr);
	  return 1;
	}

      /* For whatever reason we couldn't set a breakpoint in the dynamic
         linker.  Warn and drop into the old code.  */
    bkpt_at_symbol:
      warning ("Unable to find dynamic linker breakpoint function.\nGDB will be unable to debug shared library initializers\nand track explicitly loaded dynamic code.");
    }

  /* Scan through the list of symbols, trying to look up the symbol and
     set a breakpoint there.  Terminate loop when we/if we succeed. */

  breakpoint_addr = 0;
  for (bkpt_namep = bkpt_names; *bkpt_namep != NULL; bkpt_namep++)
    {
      msymbol = lookup_minimal_symbol (*bkpt_namep, NULL, symfile_objfile);
      if ((msymbol != NULL) && (SYMBOL_VALUE_ADDRESS (msymbol) != 0))
	{
	  create_solib_event_breakpoint (SYMBOL_VALUE_ADDRESS (msymbol));
	  return 1;
	}
    }

  /* Nothing good happened.  */
  success = 0;

#endif /* BKPT_AT_SYMBOL */

  return (success);
}