#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_12__ {size_t current; scalar_t__ expanded; } ;
struct TYPE_11__ {TYPE_1__* module; int /*<<< orphan*/  total_alloc; } ;
struct TYPE_10__ {int idx; int /*<<< orphan*/  ht_size; } ;
struct TYPE_9__ {int alloc_data; scalar_t__ dash_size; scalar_t__ pos_y; scalar_t__ idx_data; int /*<<< orphan*/  ht_size; int /*<<< orphan*/  desc; int /*<<< orphan*/  head; } ;
typedef  size_t GModule ;

/* Variables and functions */
 scalar_t__ DASH_COLLAPSED ; 
 scalar_t__ DASH_EXPANDED ; 
 TYPE_3__* dash ; 
 TYPE_7__ gdns_thread ; 
 int get_max_choices () ; 
 TYPE_4__ gscroll ; 
 TYPE_2__* holder ; 
 int /*<<< orphan*/  load_data_to_dash (TYPE_2__*,TYPE_3__*,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  module_to_desc (size_t) ; 
 int /*<<< orphan*/  module_to_head (size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
allocate_data_by_module (GModule module, int col_data)
{
  int size = 0, max_choices = get_max_choices ();

  dash->module[module].head = module_to_head (module);
  dash->module[module].desc = module_to_desc (module);

  size = holder[module].idx;
  if (gscroll.expanded && module == gscroll.current) {
    size = size > max_choices ? max_choices : holder[module].idx;
  } else {
    size = holder[module].idx > col_data ? col_data : holder[module].idx;
  }

  dash->module[module].alloc_data = size;       /* data allocated  */
  dash->module[module].ht_size = holder[module].ht_size;        /* hash table size */
  dash->module[module].idx_data = 0;
  dash->module[module].pos_y = 0;

  if (gscroll.expanded && module == gscroll.current)
    dash->module[module].dash_size = DASH_EXPANDED;
  else
    dash->module[module].dash_size = DASH_COLLAPSED;
  dash->total_alloc += dash->module[module].dash_size;

  pthread_mutex_lock (&gdns_thread.mutex);
  load_data_to_dash (&holder[module], dash, module, &gscroll);
  pthread_mutex_unlock (&gdns_thread.mutex);
}