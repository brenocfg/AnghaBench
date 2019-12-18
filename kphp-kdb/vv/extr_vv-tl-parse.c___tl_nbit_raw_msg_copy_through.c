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
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 int MSG_STD_BUFFER ; 
 int /*<<< orphan*/ * TL_IN_NBIT ; 
 int /*<<< orphan*/  TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  assert (int) ; 
 int nbit_read_in (int /*<<< orphan*/ *,void*,int) ; 
 void* rwm_postpone_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __tl_nbit_raw_msg_copy_through (int len, int advance) {
  if (advance) {
    while (len) {
      int x = len >= MSG_STD_BUFFER ? MSG_STD_BUFFER : len; 
      void *buf = rwm_postpone_alloc (TL_OUT_RAW_MSG, x);
      assert (buf);
      assert (nbit_read_in (TL_IN_NBIT, buf, x) == x);
      len -= x;
    }
  } else {
    nb_iterator_t R = *TL_IN_NBIT;
    while (len) {
      int x = len >= MSG_STD_BUFFER ? MSG_STD_BUFFER : len; 
      void *buf = rwm_postpone_alloc (TL_OUT_RAW_MSG, x);
      assert (buf);
      assert (nbit_read_in (&R, buf, x) == x);
      len -= x;
    }
  }
}