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
struct TYPE_2__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_IN_NBIT ; 
 TYPE_1__* TL_OUT_CONN ; 
 int /*<<< orphan*/  assert (int) ; 
 int nbit_copy_through (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nbit_copy_through_nondestruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __tl_nbit_conn_copy_through (int len, int advance) {
  if (advance) {
    assert (nbit_copy_through (&TL_OUT_CONN->Out, TL_IN_NBIT, len) == len);
  } else {
    assert (nbit_copy_through_nondestruct (&TL_OUT_CONN->Out, TL_IN_NBIT, len) == len);
  }
}