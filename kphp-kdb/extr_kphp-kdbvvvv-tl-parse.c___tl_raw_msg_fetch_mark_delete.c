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
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  rwm_free (scalar_t__) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void __tl_raw_msg_fetch_mark_delete (void) {
  assert (TL_IN_MARK);
  rwm_free (TL_IN_MARK);
  zfree (TL_IN_MARK, sizeof (struct raw_message));
  TL_IN_MARK = 0;
}