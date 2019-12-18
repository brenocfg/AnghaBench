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
struct section_addr_info {TYPE_1__* other; } ;
struct objfile {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  OBJF_SHARED ; 
 struct section_addr_info* alloc_section_addr_info (int) ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char*,char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  free_section_addr_info (struct section_addr_info*) ; 
 struct section_addr_info* get_relocated_section_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct section_addr_info*) ; 
 struct objfile* safe_symbol_file_add (char*,int,struct section_addr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static struct objfile *
solib_symbols_add (char *name, int from_tty, CORE_ADDR load_addr)
{
  struct section_addr_info *addrs = NULL;
  static struct objfile *result = NULL;
  bfd *abfd = NULL;

  /* The symbols in a dll are offset by 0x1000, which is the
     the offset from 0 of the first byte in an image - because
     of the file header and the section alignment. */

  if (!name || !name[0])
    return NULL;

  abfd = bfd_openr (name, "pei-i386");

  if (!abfd)
    {
      /* pei failed - try pe */
      abfd = bfd_openr (name, "pe-i386");
    }

  if (abfd)
    {
      if (bfd_check_format (abfd, bfd_object))
	{
	  addrs = get_relocated_section_addrs (abfd, load_addr);
	}

      bfd_close (abfd);
    }

  if (addrs)
    {
      result = safe_symbol_file_add (name, from_tty, addrs, 0, OBJF_SHARED);
      free_section_addr_info (addrs);
    }
  else
    {
      /* Fallback on handling just the .text section. */
      struct cleanup *my_cleanups;

      addrs = alloc_section_addr_info (1);
      my_cleanups = make_cleanup (xfree, addrs);
      addrs->other[0].name = ".text";
      addrs->other[0].addr = load_addr;

      result = safe_symbol_file_add (name, from_tty, addrs, 0, OBJF_SHARED);
      do_cleanups (my_cleanups);
    }

  return result;
}