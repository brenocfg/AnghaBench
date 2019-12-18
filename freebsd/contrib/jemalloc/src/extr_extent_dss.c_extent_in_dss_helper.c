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
 scalar_t__ dss_base ; 

__attribute__((used)) static bool
extent_in_dss_helper(void *addr, void *max) {
	return ((uintptr_t)addr >= (uintptr_t)dss_base && (uintptr_t)addr <
	    (uintptr_t)max);
}