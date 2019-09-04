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
struct TYPE_4__ {int /*<<< orphan*/  In; } ;
struct TYPE_3__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 TYPE_2__* TL_IN_CONN ; 
 TYPE_1__* TL_OUT_CONN ; 
 int /*<<< orphan*/  assert (int) ; 
 int copy_through (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int copy_through_nondestruct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void __tl_conn_conn_copy_through (int len, int advance) {
  if (advance) {
    assert (copy_through (&TL_OUT_CONN->Out, &TL_IN_CONN->In, len) == len);
  } else {
    assert (copy_through_nondestruct (&TL_OUT_CONN->Out, &TL_IN_CONN->In, len) == len);
  }
}