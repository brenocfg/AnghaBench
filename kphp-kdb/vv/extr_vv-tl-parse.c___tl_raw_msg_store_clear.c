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
 scalar_t__ TL_OUT ; 
 scalar_t__ TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  rwm_free (scalar_t__) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void __tl_raw_msg_store_clear (void) {
  if (TL_OUT_RAW_MSG) {
    rwm_free (TL_OUT_RAW_MSG);
    zfree (TL_OUT_RAW_MSG, sizeof (struct raw_message));
    TL_OUT = 0;
  }
}