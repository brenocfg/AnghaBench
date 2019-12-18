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
struct raw_message {int dummy; } ;

/* Variables and functions */
 scalar_t__ TL_IN_MARK ; 
 int TL_IN_MARK_POS ; 
 int TL_IN_POS ; 
 struct raw_message* TL_IN_RAW_MSG ; 
 int TL_IN_REMAINING ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void __tl_raw_msg_fetch_mark_restore (void) {
  assert (TL_IN_MARK);
  rwm_free (TL_IN_RAW_MSG);
  *TL_IN_RAW_MSG = *(struct raw_message *)TL_IN_MARK;
  zfree (TL_IN_MARK, sizeof (struct raw_message));
  TL_IN_MARK = 0;
  int x = TL_IN_POS - TL_IN_MARK_POS;
  TL_IN_POS -= x;
  TL_IN_REMAINING += x;
}