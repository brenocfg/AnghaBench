#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_tests; } ;
struct TYPE_4__ {int /*<<< orphan*/  invalid; } ;
typedef  TYPE_1__ GLog ;

/* Variables and functions */
 TYPE_3__ conf ; 

__attribute__((used)) static void
uncount_invalid (GLog * glog)
{
  glog->invalid -= conf.num_tests;
#ifdef TCB_BTREE
  ht_replace_genstats ("failed_requests", glog->invalid);
#endif
}