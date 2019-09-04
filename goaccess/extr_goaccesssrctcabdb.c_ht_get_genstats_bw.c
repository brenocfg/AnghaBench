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
 int /*<<< orphan*/  get_su64 (void*,char const*) ; 
 void* ht_general_stats ; 

uint64_t
ht_get_genstats_bw (const char *key)
{
  void *hash = ht_general_stats;

  if (!hash)
    return 0;

  return get_su64 (hash, key);
}