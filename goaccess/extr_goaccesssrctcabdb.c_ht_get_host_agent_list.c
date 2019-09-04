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
typedef  int /*<<< orphan*/  GSLList ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_AGENTS ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_igsl (void*,int) ; 

GSLList *
ht_get_host_agent_list (GModule module, int key)
{
  void *hash = get_hash (module, MTRC_AGENTS);
  GSLList *list;

  if ((list = get_igsl (hash, key)))
    return list;
  return NULL;
}