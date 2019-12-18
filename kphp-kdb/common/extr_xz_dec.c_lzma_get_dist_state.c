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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int DIST_STATES ; 
 scalar_t__ MATCH_LEN_MIN ; 

__attribute__((used)) static inline uint32_t lzma_get_dist_state(uint32_t len)
{
	return len < DIST_STATES + MATCH_LEN_MIN
			? len - MATCH_LEN_MIN : DIST_STATES - 1;
}