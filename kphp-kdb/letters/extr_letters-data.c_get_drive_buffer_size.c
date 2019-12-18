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
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {long long drive_l; long long drive_r; long long drive_old_mx; } ;

/* Variables and functions */
 TYPE_2__ header ; 

long long get_drive_buffer_size (int priority) {
  long long l = header.data[priority].drive_l;
  long long r = header.data[priority].drive_r;
  if (l <= r) {
    return r - l;
  } else {
    return r + header.data[priority].drive_old_mx - l;
  }
}