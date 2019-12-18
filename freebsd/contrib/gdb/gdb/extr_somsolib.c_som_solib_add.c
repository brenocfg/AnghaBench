#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
struct stat {int dummy; } ;
struct TYPE_3__ {char* name; scalar_t__ text_addr; int struct_version; int bind_mode; int library_version; int text_link_addr; int text_end; int data_start; int bss_start; int data_end; int got_value; int next; scalar_t__ tsd_start_addr; } ;
struct so_list {TYPE_1__ som_solib; scalar_t__ solib_addr; struct so_list* next; int /*<<< orphan*/ * objfile; } ;
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  obfd; } ;
typedef  int LONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 unsigned int DLD_FLAGS_LISTVALID ; 
 unsigned int DLD_FLAGS_MAPPRIVATE ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 char* alloca (unsigned int) ; 
 int auto_solib_limit ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ extract_unsigned_integer (char*,int) ; 
 int hpux_address_to_host_pointer_hack (scalar_t__) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* obsavestring (char*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* re_comp (char*) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 struct so_list* so_list_head ; 
 int /*<<< orphan*/  som_solib_add_solib_objfile (struct so_list*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  som_solib_load_symbols (struct so_list*,char*,int,scalar_t__,struct target_ops*) ; 
 int som_solib_sizeof_symbol_table (char*) ; 
 int som_solib_st_size_threshold_exceeded ; 
 int som_solib_total_st_size ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_2__* symfile_objfile ; 
 int target_read_memory (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 scalar_t__ xmalloc (int) ; 

void
som_solib_add (char *arg_string, int from_tty, struct target_ops *target, int readsyms)
{
  struct minimal_symbol *msymbol;
  struct so_list *so_list_tail;
  CORE_ADDR addr;
  asection *shlib_info;
  int status;
  unsigned int dld_flags;
  char buf[4], *re_err;
  int threshold_warning_given = 0;

  /* First validate our arguments.  */
  re_err = re_comp (arg_string ? arg_string : ".");
  if (re_err != NULL)
    {
      error ("Invalid regexp: %s", re_err);
    }

  /* If we're debugging a core file, or have attached to a running
     process, then som_solib_create_inferior_hook will not have been
     called.

     We need to first determine if we're dealing with a dynamically
     linked executable.  If not, then return without an error or warning.

     We also need to examine __dld_flags to determine if the shared library
     list is valid and to determine if the libraries have been privately
     mapped.  */
  if (symfile_objfile == NULL)
    return;

  /* First see if the objfile was dynamically linked.  */
  shlib_info = bfd_get_section_by_name (symfile_objfile->obfd, "$SHLIB_INFO$");
  if (!shlib_info)
    return;

  /* It's got a $SHLIB_INFO$ section, make sure it's not empty.  */
  if (bfd_section_size (symfile_objfile->obfd, shlib_info) == 0)
    return;

  msymbol = lookup_minimal_symbol ("__dld_flags", NULL, NULL);
  if (msymbol == NULL)
    {
      error ("Unable to find __dld_flags symbol in object file.\n");
      return;
    }

  addr = SYMBOL_VALUE_ADDRESS (msymbol);
  /* Read the current contents.  */
  status = target_read_memory (addr, buf, 4);
  if (status != 0)
    {
      error ("Unable to read __dld_flags\n");
      return;
    }
  dld_flags = extract_unsigned_integer (buf, 4);

  /* __dld_list may not be valid.  If not, then we punt, warning the user if
     we were called as a result of the add-symfile command.
   */
  if ((dld_flags & DLD_FLAGS_LISTVALID) == 0)
    {
      if (from_tty)
	error ("__dld_list is not valid according to __dld_flags.\n");
      return;
    }

  /* If the libraries were not mapped private, warn the user.  */
  if ((dld_flags & DLD_FLAGS_MAPPRIVATE) == 0)
    warning ("The shared libraries were not privately mapped; setting a\nbreakpoint in a shared library will not work until you rerun the program.\n");

  msymbol = lookup_minimal_symbol ("__dld_list", NULL, NULL);
  if (!msymbol)
    {
      /* Older crt0.o files (hpux8) don't have __dld_list as a symbol,
         but the data is still available if you know where to look.  */
      msymbol = lookup_minimal_symbol ("__dld_flags", NULL, NULL);
      if (!msymbol)
	{
	  error ("Unable to find dynamic library list.\n");
	  return;
	}
      addr = SYMBOL_VALUE_ADDRESS (msymbol) - 8;
    }
  else
    addr = SYMBOL_VALUE_ADDRESS (msymbol);

  status = target_read_memory (addr, buf, 4);
  if (status != 0)
    {
      error ("Unable to find dynamic library list.\n");
      return;
    }

  addr = extract_unsigned_integer (buf, 4);

  /* If addr is zero, then we're using an old dynamic loader which
     doesn't maintain __dld_list.  We'll have to use a completely
     different approach to get shared library information.  */
  if (addr == 0)
    goto old_dld;

  /* Using the information in __dld_list is the preferred method
     to get at shared library information.  It doesn't depend on
     any functions in /opt/langtools/lib/end.o and has a chance of working
     with hpux10 when it is released.  */
  status = target_read_memory (addr, buf, 4);
  if (status != 0)
    {
      error ("Unable to find dynamic library list.\n");
      return;
    }

  /* addr now holds the address of the first entry in the dynamic
     library list.  */
  addr = extract_unsigned_integer (buf, 4);

  /* Now that we have a pointer to the dynamic library list, walk
     through it and add the symbols for each library.  */

  so_list_tail = so_list_head;
  /* Find the end of the list of shared objects.  */
  while (so_list_tail && so_list_tail->next)
    so_list_tail = so_list_tail->next;

#ifdef SOLIB_DEBUG
  printf ("--About to read shared library list data\n");
#endif

  /* "addr" will always point to the base of the
   * current data entry describing the current
   * shared library.
   */
  while (1)
    {
      CORE_ADDR name_addr, text_addr;
      unsigned int name_len;
      char *name;
      struct so_list *new_so;
      struct so_list *so_list = so_list_head;
      struct stat statbuf;
      LONGEST st_size;
      int is_main_program;

      if (addr == 0)
	break;

      /* Get a pointer to the name of this library.  */
      status = target_read_memory (addr, buf, 4);
      if (status != 0)
	goto err;

      name_addr = extract_unsigned_integer (buf, 4);
      name_len = 0;
      while (1)
	{
	  target_read_memory (name_addr + name_len, buf, 1);
	  if (status != 0)
	    goto err;

	  name_len++;
	  if (*buf == '\0')
	    break;
	}
      name = alloca (name_len);
      status = target_read_memory (name_addr, name, name_len);
      if (status != 0)
	goto err;

      /* See if we've already loaded something with this name.  */
      while (so_list)
	{
	  if (!strcmp (so_list->som_solib.name, name))
	    break;
	  so_list = so_list->next;
	}

      /* See if the file exists.  If not, give a warning, but don't
         die.  */
      status = stat (name, &statbuf);
      if (status == -1)
	{
	  warning ("Can't find file %s referenced in dld_list.", name);

	  status = target_read_memory (addr + 36, buf, 4);
	  if (status != 0)
	    goto err;

	  addr = (CORE_ADDR) extract_unsigned_integer (buf, 4);
	  continue;
	}

      /* If we've already loaded this one or it's the main program, skip it.  */
      is_main_program = (strcmp (name, symfile_objfile->name) == 0);
      if (so_list || is_main_program)
	{
	  /* This is the "next" pointer in the strcuture.
	   */
	  status = target_read_memory (addr + 36, buf, 4);
	  if (status != 0)
	    goto err;

	  addr = (CORE_ADDR) extract_unsigned_integer (buf, 4);

	  /* Record the main program's symbol table size. */
	  if (is_main_program && !so_list)
	    {
	      st_size = som_solib_sizeof_symbol_table (name);
	      som_solib_total_st_size += st_size;
	    }

	  /* Was this a shlib that we noted but didn't load the symbols for?
	     If so, were we invoked this time from the command-line, via
	     a 'sharedlibrary' or 'add-symbol-file' command?  If yes to
	     both, we'd better load the symbols this time.
	   */
	  if (from_tty && so_list && !is_main_program && (so_list->objfile == NULL))
	    som_solib_load_symbols (so_list,
				    name,
				    from_tty,
				    so_list->som_solib.text_addr,
				    target);

	  continue;
	}

      name = obsavestring (name, name_len - 1,
			   &symfile_objfile->objfile_obstack);

      status = target_read_memory (addr + 8, buf, 4);
      if (status != 0)
	goto err;

      text_addr = extract_unsigned_integer (buf, 4);

      new_so = (struct so_list *) xmalloc (sizeof (struct so_list));
      memset ((char *) new_so, 0, sizeof (struct so_list));
      if (so_list_head == NULL)
	{
	  so_list_head = new_so;
	  so_list_tail = new_so;
	}
      else
	{
	  so_list_tail->next = new_so;
	  so_list_tail = new_so;
	}

      /* Fill in all the entries in GDB's shared library list.
       */

      new_so->solib_addr = addr;
      new_so->som_solib.name = name;
      status = target_read_memory (addr + 4, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.struct_version = extract_unsigned_integer (buf + 3, 1);
      new_so->som_solib.bind_mode = extract_unsigned_integer (buf + 2, 1);
      /* Following is "high water mark", highest version number
       * seen, rather than plain version number.
       */
      new_so->som_solib.library_version = extract_unsigned_integer (buf, 2);
      new_so->som_solib.text_addr = text_addr;

      /* Q: What about longword at "addr + 8"?
       * A: It's read above, out of order, into "text_addr".
       */

      status = target_read_memory (addr + 12, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.text_link_addr = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 16, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.text_end = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 20, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.data_start = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 24, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.bss_start = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 28, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.data_end = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 32, buf, 4);
      if (status != 0)
	goto err;

      new_so->som_solib.got_value = extract_unsigned_integer (buf, 4);

      status = target_read_memory (addr + 36, buf, 4);
      if (status != 0)
	goto err;

      /* FIXME: cagney/2003-02-01: I think som_solib.next should be a
         CORE_ADDR.  */
      new_so->som_solib.next =
	hpux_address_to_host_pointer_hack (extract_unsigned_integer (buf, 4));

      /* Note that we don't re-set "addr" to the next pointer
       * until after we've read the trailing data.
       */

      status = target_read_memory (addr + 40, buf, 4);
      new_so->som_solib.tsd_start_addr = extract_unsigned_integer (buf, 4);
      if (status != 0)
	goto err;

      /* Now indirect via that value!
       */
      status = target_read_memory (new_so->som_solib.tsd_start_addr, buf, 4);
      new_so->som_solib.tsd_start_addr = extract_unsigned_integer (buf, 4);
      if (status != 0)
	goto err;
#ifdef SOLIB_DEBUG
      printf ("\n+ library \"%s\" is described at 0x%x\n", name, addr);
      printf ("  'version' is %d\n", new_so->som_solib.struct_version);
      printf ("  'bind_mode' is %d\n", new_so->som_solib.bind_mode);
      printf ("  'library_version' is %d\n", new_so->som_solib.library_version);
      printf ("  'text_addr' is 0x%x\n", new_so->som_solib.text_addr);
      printf ("  'text_link_addr' is 0x%x\n", new_so->som_solib.text_link_addr);
      printf ("  'text_end' is 0x%x\n", new_so->som_solib.text_end);
      printf ("  'data_start' is 0x%x\n", new_so->som_solib.data_start);
      printf ("  'bss_start' is 0x%x\n", new_so->som_solib.bss_start);
      printf ("  'data_end' is 0x%x\n", new_so->som_solib.data_end);
      printf ("  'got_value' is %x\n", new_so->som_solib.got_value);
      printf ("  'next' is 0x%x\n", new_so->som_solib.next);
      printf ("  'tsd_start_addr' is 0x%x\n", new_so->som_solib.tsd_start_addr);
#endif

      /* Go on to the next shared library descriptor.
       */
      addr = (CORE_ADDR) new_so->som_solib.next;



      /* At this point, we have essentially hooked the shlib into the
         "info share" command.  However, we haven't yet loaded its
         symbol table.  We must now decide whether we ought to, i.e.,
         whether doing so would exceed the symbol table size threshold.

         If the threshold has just now been exceeded, then we'll issue
         a warning message (which explains how to load symbols manually,
         if the user so desires).

         If the threshold has just now or previously been exceeded,
         we'll just add the shlib to the list of object files, but won't
         actually load its symbols.  (This is more useful than it might
         sound, for it allows us to e.g., still load and use the shlibs'
         unwind information for stack tracebacks.)
       */

      /* Note that we DON'T want to preclude the user from using the
         add-symbol-file command!  Thus, we only worry about the threshold
         when we're invoked for other reasons.
       */
      st_size = som_solib_sizeof_symbol_table (name);
      som_solib_st_size_threshold_exceeded =
	!from_tty &&
	auto_solib_limit > 0 &&
	readsyms &&
	((st_size + som_solib_total_st_size) > (auto_solib_limit * (LONGEST) (1024 * 1024)));

      if (som_solib_st_size_threshold_exceeded)
	{
	  if (!threshold_warning_given)
	    warning ("Symbols for some libraries have not been loaded, because\ndoing so would exceed the size threshold specified by auto-solib-limit.\nTo manually load symbols, use the 'sharedlibrary' command.\nTo raise the threshold, set auto-solib-limit to a larger value and rerun\nthe program.\n");
	  threshold_warning_given = 1;

	  /* We'll still make note of this shlib, even if we don't
	     read its symbols.  This allows us to use its unwind
	     information well enough to know how to e.g., correctly
	     do a traceback from a PC within the shlib, even if we
	     can't symbolize those PCs...
	   */
	  som_solib_add_solib_objfile (new_so, name, from_tty, text_addr);
	  continue;
	}

      som_solib_total_st_size += st_size;

      /* This fills in new_so->objfile, among others. */
      som_solib_load_symbols (new_so, name, from_tty, text_addr, target);
    }

#ifdef SOLIB_DEBUG
  printf ("--Done reading shared library data\n");
#endif

  /* Getting new symbols may change our opinion about what is
     frameless.  */
  reinit_frame_cache ();
  return;

old_dld:
  error ("Debugging dynamic executables loaded via the hpux8 dld.sl is not supported.\n");
  return;

err:
  error ("Error while reading dynamic library list.\n");
  return;
}