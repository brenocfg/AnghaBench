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
struct TYPE_2__ {scalar_t__ excluded_ip; scalar_t__ invalid; scalar_t__ processed; scalar_t__ valid; } ;

/* Variables and functions */
 TYPE_1__* glog ; 

__attribute__((used)) static void
set_general_stats (void)
{
  glog->valid = glog->processed = glog->invalid = glog->excluded_ip = 0;

#ifdef TCB_BTREE
  glog->excluded_ip = ht_get_genstats ("excluded_ip");
  glog->invalid = ht_get_genstats ("failed_requests");
  glog->processed = ht_get_genstats ("total_requests");
  glog->resp_size = ht_get_genstats_bw ("bandwidth");
  glog->valid = ht_get_genstats ("valid_requests");

  if (glog->resp_size > 0)
    conf.bandwidth = 1;
  if (ht_get_genstats ("serve_usecs"))
    conf.serve_usecs = 1;
#endif
}