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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 void* ht_general_stats ; 
 int inc_su64 (void*,char const*,int /*<<< orphan*/ ) ; 

int
ht_insert_genstats_bw (const char *key, uint64_t inc)
{
  void *hash = ht_general_stats;

  if (!hash)
    return -1;

  return inc_su64 (hash, key, inc);
}