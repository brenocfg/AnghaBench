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
typedef  void GSLList ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTS ; 
 int /*<<< orphan*/  free (void*) ; 
 void* ht_get_host_agent_list (int /*<<< orphan*/ ,int) ; 
 int ht_get_keymap (int /*<<< orphan*/ ,char const*) ; 
 int list_count (void*) ; 

int
set_host_agents (const char *addr, void (*func) (void *, void *, int),
                 void *arr)
{
  GSLList *list;
  int data_nkey, count = 0;

  data_nkey = ht_get_keymap (HOSTS, addr);
  if (data_nkey == 0)
    return 1;

  list = ht_get_host_agent_list (HOSTS, data_nkey);
  if (!list)
    return 1;

  if ((count = list_count (list)) == 0) {
    free (list);
    return 1;
  }

  func (list, arr, count);

#ifdef TCB_MEMHASH
  free (list);
#endif

  return 0;
}