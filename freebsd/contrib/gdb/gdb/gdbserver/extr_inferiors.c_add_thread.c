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
struct TYPE_2__ {int id; } ;
struct thread_info {void* target_data; TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_inferior_to_list (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  all_threads ; 
 struct thread_info* current_inferior ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct thread_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_register_cache () ; 
 int /*<<< orphan*/  set_inferior_regcache_data (struct thread_info*,int /*<<< orphan*/ ) ; 

void
add_thread (int thread_id, void *target_data)
{
  struct thread_info *new_thread
    = (struct thread_info *) malloc (sizeof (*new_thread));

  memset (new_thread, 0, sizeof (*new_thread));

  new_thread->entry.id = thread_id;

  add_inferior_to_list (&all_threads, & new_thread->entry);
  
  if (current_inferior == NULL)
    current_inferior = new_thread;

  new_thread->target_data = target_data;
  set_inferior_regcache_data (new_thread, new_register_cache ());
}