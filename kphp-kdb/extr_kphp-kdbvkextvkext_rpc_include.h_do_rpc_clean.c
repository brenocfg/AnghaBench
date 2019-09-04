#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_clear (scalar_t__) ; 
 scalar_t__ buffer_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_write_reserve (scalar_t__,int) ; 
 scalar_t__ outbuf ; 
 int /*<<< orphan*/  store ; 

__attribute__((used)) static void do_rpc_clean (void) { /* {{{ */
  ADD_CNT (store);
  START_TIMER (store);
  if (outbuf) {
    buffer_clear (outbuf);
  } else {
    outbuf = buffer_create (0);
  }
  buffer_write_reserve (outbuf, 40);
  END_TIMER (store);
}