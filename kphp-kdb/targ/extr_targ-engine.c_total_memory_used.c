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
struct treespace_header {long long used_ints; } ;

/* Variables and functions */
 scalar_t__ AdSpace ; 
 scalar_t__ WordSpace ; 
 scalar_t__ allocated_metafile_bytes ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 scalar_t__ dyn_top ; 
 scalar_t__ tot_userlists_size ; 

long long total_memory_used (void) {
  long long res = (long) (dyn_cur - dyn_first + dyn_last - dyn_top);
  res += (AdSpace ? ((struct treespace_header *)AdSpace)->used_ints : 0) * 4LL; 
  res += ((struct treespace_header *)WordSpace)->used_ints * 4LL;
  res += tot_userlists_size;
  res += allocated_metafile_bytes;
  return res;
}