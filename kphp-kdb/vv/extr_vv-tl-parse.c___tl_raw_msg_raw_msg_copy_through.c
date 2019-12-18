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
 int /*<<< orphan*/  TL_IN_RAW_MSG ; 
 int /*<<< orphan*/  TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  rwm_clone (struct raw_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwm_split_head (struct raw_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwm_trunc (struct raw_message*,int) ; 
 int /*<<< orphan*/  rwm_union (int /*<<< orphan*/ ,struct raw_message*) ; 

__attribute__((used)) static inline void __tl_raw_msg_raw_msg_copy_through (int len, int advance) {
  if (!advance) {
    struct raw_message r;
    rwm_clone (&r, TL_IN_RAW_MSG);
    rwm_trunc (&r, len);
    rwm_union (TL_OUT_RAW_MSG, &r);
  } else {
    struct raw_message r;
    rwm_split_head (&r, TL_IN_RAW_MSG, len);
    rwm_union (TL_OUT_RAW_MSG, &r);
  }
}