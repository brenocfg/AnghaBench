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
 void* ht_general_stats ; 
 int ins_si32 (void*,char const*,int) ; 

int
ht_replace_genstats (const char *key, int value)
{
  void *hash = ht_general_stats;

  if (!hash)
    return -1;

  return ins_si32 (hash, key, value);
}