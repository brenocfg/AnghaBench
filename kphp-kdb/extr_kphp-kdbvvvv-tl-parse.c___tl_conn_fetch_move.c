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
struct TYPE_2__ {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 TYPE_1__* TL_IN_CONN ; 
 int advance_skip_read_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void __tl_conn_fetch_move (int len) {
  if (len >= 0) {
    assert (advance_skip_read_ptr (&TL_IN_CONN->In, len) == len);
  } else {
    assert (0);
  }
}