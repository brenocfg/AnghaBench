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
struct so_list {struct so_list* next; TYPE_1__* lm_info; } ;
struct read_map_ctxt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  isloader; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_map (struct read_map_ctxt*) ; 
 int /*<<< orphan*/  memcpy (struct so_list*,struct so_list*,int) ; 
 int /*<<< orphan*/  open_map (struct read_map_ctxt*) ; 
 int /*<<< orphan*/  osf_free_so (struct so_list*) ; 
 int /*<<< orphan*/  read_map (struct read_map_ctxt*,struct so_list*) ; 
 struct so_list* xmalloc (int) ; 

__attribute__((used)) static struct so_list *
osf_current_sos (void)
{
  struct so_list *head = NULL, *tail, *newtail, so;
  struct read_map_ctxt ctxt;
  int skipped_main;

  if (!open_map (&ctxt))
    return NULL;

  /* Read subsequent elements.  */
  for (skipped_main = 0;;)
    {
      if (!read_map (&ctxt, &so))
	break;

      /* Skip the main program module, which is first in the list after
         /sbin/loader.  */
      if (!so.lm_info->isloader && !skipped_main)
	{
	  osf_free_so (&so);
	  skipped_main = 1;
	  continue;
	}

      newtail = xmalloc (sizeof *newtail);
      if (!head)
	head = newtail;
      else
	tail->next = newtail;
      tail = newtail;

      memcpy (tail, &so, sizeof so);
      tail->next = NULL;
    }

 done:
  close_map (&ctxt);
  return head;
}