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
struct TYPE_2__ {int log_wptr; int log_rptr; scalar_t__ log_start; scalar_t__ log_endw; } ;

/* Variables and functions */
 TYPE_1__ W ; 

int compute_uncommitted_log_bytes (void) {
  int log_uncommitted = W.log_wptr - W.log_rptr;
  if (log_uncommitted < 0) {
    log_uncommitted += W.log_endw - W.log_start;
  }
  return log_uncommitted;
}