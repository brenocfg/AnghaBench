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
 int /*<<< orphan*/  TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rwm_clone (struct raw_message*,int /*<<< orphan*/ ) ; 
 int rwm_fetch_data_back (struct raw_message*,void*,int) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 

__attribute__((used)) static inline void __tl_raw_msg_store_read_back_nondestruct (void *buf, int len) {
  struct raw_message r;
  rwm_clone (&r, TL_OUT_RAW_MSG);
  assert (rwm_fetch_data_back (&r, buf, len) == len);
  rwm_free (&r);
}