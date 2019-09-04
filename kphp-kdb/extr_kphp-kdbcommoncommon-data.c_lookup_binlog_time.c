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
struct TYPE_2__ {long long pos; } ;

/* Variables and functions */
 int BINLOGPOS_QUEUE_SIZE ; 
 TYPE_1__* fbd_data ; 
 int fbd_rptr ; 
 int fbd_wptr ; 
 int lookup_binlog_binsearch (long long,int,int) ; 

long long lookup_binlog_time (long long binlog_time) {
  int res;
  if (fbd_rptr > fbd_wptr) {
    res = lookup_binlog_binsearch (binlog_time, fbd_rptr, BINLOGPOS_QUEUE_SIZE);
    if (res < BINLOGPOS_QUEUE_SIZE) {  
      return fbd_data[res].pos;
    }
    res = lookup_binlog_binsearch (binlog_time, 0, fbd_wptr);
  } else {
    res = lookup_binlog_binsearch (binlog_time, fbd_rptr, fbd_wptr);
  }
  return res == fbd_wptr ? 0 : fbd_data[res].pos;
}