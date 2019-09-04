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

__attribute__((used)) static inline void __tl_raw_msg_fetch_lookup (void *buf, int len) {
#ifdef ENABLE_UDP
  assert (rwm_fetch_lookup (TL_IN_RAW_MSG, buf, len) == len);
#endif
}