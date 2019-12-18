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
typedef  int /*<<< orphan*/  nb_iterator_t ;
struct TYPE_2__ {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int MSG_STD_BUFFER ; 
 TYPE_1__* TL_IN_CONN ; 
 int /*<<< orphan*/  TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nbit_clear (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_in (int /*<<< orphan*/ *,void*,int) ; 
 void* rwm_postpone_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __tl_conn_raw_msg_copy_through (int len, int advance) {
  if (advance) {
    while (len) {
      int x = len >= MSG_STD_BUFFER ? MSG_STD_BUFFER : len; 
      void *buf = rwm_postpone_alloc (TL_OUT_RAW_MSG, x);
      assert (buf);
      assert (read_in (&TL_IN_CONN->In, buf, x) == x);
      len -= x;
    }
  } else {
    nb_iterator_t R;
    nbit_set (&R, &TL_IN_CONN->In);
    while (len) {
      int x = len >= MSG_STD_BUFFER ? MSG_STD_BUFFER : len; 
      void *buf = rwm_postpone_alloc (TL_OUT_RAW_MSG, x);
      assert (buf);
      assert (nbit_read_in (&R, buf, x) == x);
      len -= x;
    }
    nbit_clear (&R);
  }
}