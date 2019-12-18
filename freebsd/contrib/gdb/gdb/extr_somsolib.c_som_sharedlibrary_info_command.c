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
struct TYPE_2__ {int struct_version; int bind_mode; unsigned int library_version; unsigned int text_addr; unsigned int text_end; unsigned int data_start; unsigned int data_end; unsigned int got_value; int /*<<< orphan*/  name; } ;
struct so_list {struct so_list* next; TYPE_1__ som_solib; int /*<<< orphan*/ * objfile; } ;

/* Variables and functions */
 int /*<<< orphan*/ * exec_bfd ; 
 int /*<<< orphan*/  local_hex_string_custom (unsigned int,char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 struct so_list* so_list_head ; 

__attribute__((used)) static void
som_sharedlibrary_info_command (char *ignore, int from_tty)
{
  struct so_list *so_list = so_list_head;

  if (exec_bfd == NULL)
    {
      printf_unfiltered ("No executable file.\n");
      return;
    }

  if (so_list == NULL)
    {
      printf_unfiltered ("No shared libraries loaded at this time.\n");
      return;
    }

  printf_unfiltered ("Shared Object Libraries\n");
  printf_unfiltered ("    %-12s%-12s%-12s%-12s%-12s%-12s\n",
	 "  flags", "  tstart", "   tend", "  dstart", "   dend", "   dlt");
  while (so_list)
    {
      unsigned int flags;

      flags = so_list->som_solib.struct_version << 24;
      flags |= so_list->som_solib.bind_mode << 16;
      flags |= so_list->som_solib.library_version;
      printf_unfiltered ("%s", so_list->som_solib.name);
      if (so_list->objfile == NULL)
	printf_unfiltered ("  (symbols not loaded)");
      printf_unfiltered ("\n");
      printf_unfiltered ("    %-12s", local_hex_string_custom (flags, "08l"));
      printf_unfiltered ("%-12s",
	     local_hex_string_custom (so_list->som_solib.text_addr, "08l"));
      printf_unfiltered ("%-12s",
	      local_hex_string_custom (so_list->som_solib.text_end, "08l"));
      printf_unfiltered ("%-12s",
	    local_hex_string_custom (so_list->som_solib.data_start, "08l"));
      printf_unfiltered ("%-12s",
	      local_hex_string_custom (so_list->som_solib.data_end, "08l"));
      printf_unfiltered ("%-12s\n",
	     local_hex_string_custom (so_list->som_solib.got_value, "08l"));
      so_list = so_list->next;
    }
}