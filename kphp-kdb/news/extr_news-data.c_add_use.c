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
struct TYPE_2__ {size_t next; int prev; } ;

/* Variables and functions */
 TYPE_1__* large_metafiles ; 
 size_t large_users_number ; 

void add_use (int pos) {
  large_metafiles[pos].next = large_users_number;
  large_metafiles[pos].prev = large_metafiles[large_users_number].prev;
  large_metafiles[large_metafiles[pos].next].prev = pos;
  large_metafiles[large_metafiles[pos].prev].next = pos;
}