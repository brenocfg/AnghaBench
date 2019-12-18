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
 scalar_t__ is_mbm_local_enabled () ; 
 scalar_t__ is_mbm_total_enabled () ; 

__attribute__((used)) static inline bool is_mbm_enabled(void)
{
	return (is_mbm_total_enabled() || is_mbm_local_enabled());
}