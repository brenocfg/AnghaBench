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
 int /*<<< orphan*/  TL_IN_RAW_MSG ; 
 int /*<<< orphan*/  TL_OUT_CONN ; 
 int /*<<< orphan*/  __m_to_conn ; 
 int /*<<< orphan*/  assert (int) ; 
 int rwm_process (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rwm_process_and_advance (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __tl_raw_msg_conn_copy_through (int len, int advance) {
  if (advance) {
    assert (rwm_process_and_advance (TL_IN_RAW_MSG, len, __m_to_conn, TL_OUT_CONN) == len);
  } else {
    assert (rwm_process (TL_IN_RAW_MSG, len, __m_to_conn, TL_OUT_CONN) == len);
  }
}