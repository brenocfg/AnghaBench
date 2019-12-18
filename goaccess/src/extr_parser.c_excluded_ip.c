#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ignore_ip_idx; } ;
struct TYPE_7__ {int /*<<< orphan*/  excluded_ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ GLogItem ;
typedef  TYPE_2__ GLog ;

/* Variables and functions */
 TYPE_5__ conf ; 
 int /*<<< orphan*/  ht_insert_genstats (char*,int) ; 
 scalar_t__ ip_in_range (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
excluded_ip (GLog * glog, GLogItem * logitem)
{
  if (conf.ignore_ip_idx && ip_in_range (logitem->host)) {
    glog->excluded_ip++;
#ifdef TCB_BTREE
    ht_insert_genstats ("excluded_ip", 1);
#endif
    return 0;
  }
  return 1;
}