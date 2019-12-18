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
struct link_map_offsets {scalar_t__ l_name_offset; int /*<<< orphan*/  l_name_size; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SO_NAME_MAX_PATH_SIZE ; 
 struct link_map_offsets* SVR4_FETCH_LINK_MAP_OFFSETS () ; 
 int /*<<< orphan*/  debug_base ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ first_link_map_member () ; 
 int /*<<< orphan*/  locate_base () ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  query (char*) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 int /*<<< orphan*/  symbol_file_add_main (char*,int) ; 
 scalar_t__ symfile_objfile ; 
 int /*<<< orphan*/  target_read_string (scalar_t__,char**,scalar_t__,int*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_symbol_file_object (void *from_ttyp)
{
  CORE_ADDR lm, l_name;
  char *filename;
  int errcode;
  int from_tty = *(int *)from_ttyp;
  struct link_map_offsets *lmo = SVR4_FETCH_LINK_MAP_OFFSETS ();
  char *l_name_buf = xmalloc (lmo->l_name_size);
  struct cleanup *cleanups = make_cleanup (xfree, l_name_buf);

  if (symfile_objfile)
    if (!query ("Attempt to reload symbols from process? "))
      return 0;

  if ((debug_base = locate_base ()) == 0)
    return 0;	/* failed somehow... */

  /* First link map member should be the executable.  */
  if ((lm = first_link_map_member ()) == 0)
    return 0;	/* failed somehow... */

  /* Read address of name from target memory to GDB.  */
  read_memory (lm + lmo->l_name_offset, l_name_buf, lmo->l_name_size);

  /* Convert the address to host format.  Assume that the address is
     unsigned.  */
  l_name = extract_unsigned_integer (l_name_buf, lmo->l_name_size);

  /* Free l_name_buf.  */
  do_cleanups (cleanups);

  if (l_name == 0)
    return 0;		/* No filename.  */

  /* Now fetch the filename from target memory.  */
  target_read_string (l_name, &filename, SO_NAME_MAX_PATH_SIZE - 1, &errcode);

  if (errcode)
    {
      warning ("failed to read exec filename from attached file: %s",
	       safe_strerror (errcode));
      return 0;
    }

  make_cleanup (xfree, filename);
  /* Have a pathname: read the symbol file.  */
  symbol_file_add_main (filename, from_tty);

  return 1;
}