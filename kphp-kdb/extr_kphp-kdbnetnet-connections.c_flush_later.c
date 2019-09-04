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
struct connection {int flags; int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int C_DFLUSH ; 
 int C_INCONN ; 
 scalar_t__ out_total_processed_bytes (struct connection*) ; 
 scalar_t__ out_total_unprocessed_bytes (struct connection*) ; 
 int /*<<< orphan*/  put_event_into_heap (int /*<<< orphan*/ ) ; 

int flush_later (struct connection *c) {
  if (out_total_processed_bytes (c) + out_total_unprocessed_bytes (c) > 0) {
    if (c->flags & C_DFLUSH) {
      return 1;
    }
    c->flags |= C_DFLUSH;
    if (!(c->flags & C_INCONN)) {
      put_event_into_heap (c->ev);
    }
    return 2;
  }
  return 0;
}