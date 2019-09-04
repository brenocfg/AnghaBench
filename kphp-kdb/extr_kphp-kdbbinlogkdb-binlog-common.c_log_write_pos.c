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
struct TYPE_2__ {scalar_t__ log_rptr; scalar_t__ log_wptr; long long log_endw; long long log_start; } ;

/* Variables and functions */
 TYPE_1__ W ; 
 int /*<<< orphan*/  assert (long long) ; 
 long long log_pos ; 

long long log_write_pos (void) {
  if (W.log_rptr <= W.log_wptr) {
    return log_pos + (W.log_wptr - W.log_rptr);
  } else {
    assert (W.log_endw);
    return log_pos + (W.log_wptr - W.log_start) + (W.log_endw - W.log_rptr);
  }
}