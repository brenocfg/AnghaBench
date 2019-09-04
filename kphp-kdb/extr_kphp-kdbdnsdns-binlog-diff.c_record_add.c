#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ record_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_logevents ; 
 void* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_uncommitted_log_bytes () ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  try_change_zone () ; 

__attribute__((used)) static void record_add (record_t *r) {
  try_change_zone ();
  assert (r->data_len >= 4);
  void *E = alloc_log_event (0, r->data_len, 0);
  memcpy (E, r->data, r->data_len);
  if (compute_uncommitted_log_bytes () > (1 << 23)) {
    flush_binlog_forced (0);
  }
  add_logevents++;
}