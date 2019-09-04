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
 int /*<<< orphan*/  TL_OUT_RAW_MSG ; 
 int /*<<< orphan*/  assert (int) ; 
 int rwm_push_data (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static inline void __tl_raw_msg_store_raw_data (const void *buf, int len) {
  assert (rwm_push_data (TL_OUT_RAW_MSG, buf, len) == len);
}