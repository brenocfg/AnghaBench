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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 void* ht_general_stats ; 
 int inc_si32 (void*,char*,int) ; 

int
ht_insert_genstats_accumulated_time (time_t elapsed)
{
  void *hash = ht_general_stats;

  if (!hash)
    return 0;

  return inc_si32 (hash, "accumulated_time", (int) elapsed) != -1;
}