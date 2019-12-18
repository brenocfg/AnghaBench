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
struct objfile {char* name; int flags; } ;
struct lm_info {char* lm; } ;
struct link_map_offsets {int l_next_offset; int /*<<< orphan*/  l_next_size; int /*<<< orphan*/  l_name_size; scalar_t__ l_name_offset; int /*<<< orphan*/  link_map_size; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int OBJF_SHARED ; 
 scalar_t__ SO_NAME_MAX_PATH_SIZE ; 
 struct link_map_offsets* SVR4_FETCH_LINK_MAP_OFFSETS () ; 
 int /*<<< orphan*/  debug_base ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ first_link_map_member () ; 
 int /*<<< orphan*/  locate_base () ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  target_read_string (scalar_t__,char**,scalar_t__,int*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 void* xmalloc (int /*<<< orphan*/ ) ; 

CORE_ADDR
svr4_fetch_objfile_link_map (struct objfile *objfile)
{
  CORE_ADDR lm;

  if ((debug_base = locate_base ()) == 0)
    return 0;   /* failed somehow... */

  /* Position ourselves on the first link map.  */
  lm = first_link_map_member ();  
  while (lm)
    {
      /* Get info on the layout of the r_debug and link_map structures. */
      struct link_map_offsets *lmo = SVR4_FETCH_LINK_MAP_OFFSETS ();
      int errcode;
      char *buffer;
      struct lm_info objfile_lm_info;
      struct cleanup *old_chain;
      CORE_ADDR name_address;
      char *l_name_buf = xmalloc (lmo->l_name_size);
      old_chain = make_cleanup (xfree, l_name_buf);

      /* Set up the buffer to contain the portion of the link_map
         structure that gdb cares about.  Note that this is not the
         whole link_map structure.  */
      objfile_lm_info.lm = xmalloc (lmo->link_map_size);
      make_cleanup (xfree, objfile_lm_info.lm);
      memset (objfile_lm_info.lm, 0, lmo->link_map_size);

      /* Read the link map into our internal structure.  */
      read_memory (lm, objfile_lm_info.lm, lmo->link_map_size);

      /* Read address of name from target memory to GDB.  */
      read_memory (lm + lmo->l_name_offset, l_name_buf, lmo->l_name_size);

      /* Extract this object's name.  Assume that the address is
         unsigned.  */
      name_address = extract_unsigned_integer (l_name_buf, lmo->l_name_size);
      target_read_string (name_address, &buffer,
      			  SO_NAME_MAX_PATH_SIZE - 1, &errcode);
      make_cleanup (xfree, buffer);
      if (errcode != 0)
    	{
	  warning ("svr4_fetch_objfile_link_map: Can't read pathname for load map: %s\n",
  		   safe_strerror (errcode));
  	}
      else
  	{
	  /* Is this the linkmap for the file we want?  */
	  /* If the file is not a shared library and has no name,
	     we are sure it is the main executable, so we return that.  */
	  if ((buffer && strcmp (buffer, objfile->name) == 0)
              || (!(objfile->flags & OBJF_SHARED) && (strcmp (buffer, "") == 0)))
  	    {
    	      do_cleanups (old_chain);
    	      return lm;
      	    }
  	}
      /* Not the file we wanted, continue checking.  Assume that the
         address is unsigned.  */
      lm = extract_unsigned_integer (objfile_lm_info.lm + lmo->l_next_offset,
				     lmo->l_next_size);
      do_cleanups (old_chain);
    }
  return 0;
}