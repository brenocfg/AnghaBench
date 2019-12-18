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
typedef  size_t const uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t time_win_to_unix(uint64_t win_time) {
	const size_t ns_in_sec = 10000000;
	const uint64_t sec_to_unix = 11644473600LL;
	return win_time / ns_in_sec - sec_to_unix;
}