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

/* Variables and functions */
 char* get_is32 (void*,int) ; 
 void* ht_agent_vals ; 

char *
ht_get_host_agent_val (int key)
{
  void *hash = ht_agent_vals;

  if (!hash)
    return NULL;

  return get_is32 (hash, key);
}