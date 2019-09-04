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
struct TYPE_2__ {int serve_usecs; } ;

/* Variables and functions */
 TYPE_1__ conf ; 

__attribute__((used)) static void
contains_usecs (void)
{
  if (conf.serve_usecs)
    return;

#ifdef TCB_BTREE
  ht_insert_genstats ("serve_usecs", 1);
#endif
  conf.serve_usecs = 1; /* flag */
}