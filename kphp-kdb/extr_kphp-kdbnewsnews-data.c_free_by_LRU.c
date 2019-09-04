#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t next; } ;

/* Variables and functions */
 TYPE_1__* large_metafiles ; 
 size_t large_users_number ; 
 int unload_metafile (size_t) ; 

int free_by_LRU (void) {
  if (large_metafiles[large_users_number].next == large_users_number) {
    return 0;
  }
  return unload_metafile (large_metafiles[large_users_number].next);
}