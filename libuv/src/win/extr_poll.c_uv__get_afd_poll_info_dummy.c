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
typedef  int /*<<< orphan*/  AFD_POLL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  afd_poll_info_dummy_ ; 

__attribute__((used)) static AFD_POLL_INFO* uv__get_afd_poll_info_dummy(void) {
  return &afd_poll_info_dummy_;
}