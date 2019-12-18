#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ GLog ;

/* Variables and functions */
 int /*<<< orphan*/  ht_insert_genstats (char*,int) ; 
 int /*<<< orphan*/  lock_spinner () ; 
 int /*<<< orphan*/  unlock_spinner () ; 

__attribute__((used)) static void
count_valid (GLog * glog)
{
  lock_spinner ();
  glog->valid++;
#ifdef TCB_BTREE
  ht_insert_genstats ("valid_requests", 1);
#endif
  unlock_spinner ();
}