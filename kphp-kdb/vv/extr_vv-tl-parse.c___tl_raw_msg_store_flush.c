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
struct udp_target {int dummy; } ;
struct raw_message {int dummy; } ;

/* Variables and functions */
 scalar_t__ TL_OUT ; 
 scalar_t__ TL_OUT_EXTRA ; 
 scalar_t__ TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  udp_target_send (struct udp_target*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void __tl_raw_msg_store_flush (void) {
//  struct udp_target *S = (struct udp_target *)TL_OUT_EXTRA;
  assert (TL_OUT_RAW_MSG);
  assert (TL_OUT_EXTRA);
  udp_target_send ((struct udp_target *)TL_OUT_EXTRA, TL_OUT_RAW_MSG, 0);
  zfree (TL_OUT_RAW_MSG, sizeof (struct raw_message));
  TL_OUT = 0;
  //udp_target_flush ((struct udp_target *)TL_OUT_EXTRA);
}