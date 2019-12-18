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
struct thread_info {int dummy; } ;
struct inferior_regcache_data {scalar_t__ registers_valid; } ;
struct inferior_list_entry {int dummy; } ;

/* Variables and functions */
 struct thread_info* current_inferior ; 
 scalar_t__ inferior_regcache_data (struct thread_info*) ; 
 int /*<<< orphan*/  store_inferior_registers (int) ; 

void
regcache_invalidate_one (struct inferior_list_entry *entry)
{
  struct thread_info *thread = (struct thread_info *) entry;
  struct inferior_regcache_data *regcache;

  regcache = (struct inferior_regcache_data *) inferior_regcache_data (thread);

  if (regcache->registers_valid)
    {
      struct thread_info *saved_inferior = current_inferior;

      current_inferior = thread;
      store_inferior_registers (-1);
      current_inferior = saved_inferior;
    }

  regcache->registers_valid = 0;
}