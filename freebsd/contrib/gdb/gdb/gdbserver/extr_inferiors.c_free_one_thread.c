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
struct inferior_list_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct thread_info*) ; 
 int /*<<< orphan*/  free_register_cache (int /*<<< orphan*/ ) ; 
 struct thread_info* get_thread (struct inferior_list_entry*) ; 
 int /*<<< orphan*/  inferior_regcache_data (struct thread_info*) ; 

__attribute__((used)) static void
free_one_thread (struct inferior_list_entry *inf)
{
  struct thread_info *thread = get_thread (inf);
  free_register_cache (inferior_regcache_data (thread));
  free (thread);
}