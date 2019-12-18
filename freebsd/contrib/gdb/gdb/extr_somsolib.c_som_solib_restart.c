#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct so_list {struct so_list* next; } ;
struct TYPE_15__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_14__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_13__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_12__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_11__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_10__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_9__ {int /*<<< orphan*/ * unwind; scalar_t__ address; } ;
struct TYPE_16__ {TYPE_7__ unload_stub; TYPE_6__ unload2; TYPE_5__ unload; TYPE_4__ load_stub; TYPE_3__ load; TYPE_2__ hook_stub; TYPE_1__ hook; scalar_t__ is_valid; } ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  disable_breakpoints_in_shlibs (int /*<<< orphan*/ ) ; 
 TYPE_8__ dld_cache ; 
 struct so_list* so_list_head ; 
 scalar_t__ som_solib_st_size_threshold_exceeded ; 
 scalar_t__ som_solib_total_st_size ; 
 int /*<<< orphan*/  xfree (struct so_list*) ; 

void
som_solib_restart (void)
{
  struct so_list *sl = so_list_head;

  /* Before the shlib info vanishes, use it to disable any breakpoints
     that may still be active in those shlibs.
   */
  disable_breakpoints_in_shlibs (0);

  /* Discard all the shlib descriptors.
   */
  while (sl)
    {
      struct so_list *next_sl = sl->next;
      xfree (sl);
      sl = next_sl;
    }
  so_list_head = NULL;

  som_solib_total_st_size = (LONGEST) 0;
  som_solib_st_size_threshold_exceeded = 0;

  dld_cache.is_valid = 0;

  dld_cache.hook.address = 0;
  dld_cache.hook.unwind = NULL;

  dld_cache.hook_stub.address = 0;
  dld_cache.hook_stub.unwind = NULL;

  dld_cache.load.address = 0;
  dld_cache.load.unwind = NULL;

  dld_cache.load_stub.address = 0;
  dld_cache.load_stub.unwind = NULL;

  dld_cache.unload.address = 0;
  dld_cache.unload.unwind = NULL;

  dld_cache.unload2.address = 0;
  dld_cache.unload2.unwind = NULL;

  dld_cache.unload_stub.address = 0;
  dld_cache.unload_stub.unwind = NULL;
}