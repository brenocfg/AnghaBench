#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bandwidth; int serve_usecs; } ;
struct TYPE_3__ {scalar_t__ resp_size; void* valid; void* processed; void* invalid; void* excluded_ip; } ;

/* Variables and functions */
 TYPE_2__ conf ; 
 TYPE_1__* glog ; 
 void* ht_get_genstats (char*) ; 
 scalar_t__ ht_get_genstats_bw (char*) ; 

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