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
struct so_list {int /*<<< orphan*/  so_name; TYPE_1__* lm_info; } ;
struct read_map_ctxt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  isloader; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_map (struct read_map_ctxt*) ; 
 int /*<<< orphan*/  open_map (struct read_map_ctxt*) ; 
 int /*<<< orphan*/  osf_free_so (struct so_list*) ; 
 int /*<<< orphan*/  query (char*) ; 
 int /*<<< orphan*/  read_map (struct read_map_ctxt*,struct so_list*) ; 
 int /*<<< orphan*/  symbol_file_add_main (int /*<<< orphan*/ ,int) ; 
 scalar_t__ symfile_objfile ; 

__attribute__((used)) static int
osf_open_symbol_file_object (void *from_ttyp)
{
  struct read_map_ctxt ctxt;
  struct so_list so;
  int found;

  if (symfile_objfile)
    if (!query ("Attempt to reload symbols from process? "))
      return 0;

  /* The first module after /sbin/loader is the main program.  */
  if (!open_map (&ctxt))
    return 0;
  for (found = 0; !found;)
    {
      if (!read_map (&ctxt, &so))
	break;
      found = !so.lm_info->isloader;
      osf_free_so (&so);
    }
  close_map (&ctxt);

  if (found)
    symbol_file_add_main (so.so_name, *(int *) from_ttyp);
  return found;
}