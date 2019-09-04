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
 scalar_t__ MAX_DEPTH ; 
 int /*<<< orphan*/  die (char*,scalar_t__) ; 
 scalar_t__ max_depth ; 
 scalar_t__ ulong_arg (char*,char const*) ; 

__attribute__((used)) static void option_depth(const char *depth)
{
	max_depth = ulong_arg("--depth", depth);
	if (max_depth > MAX_DEPTH)
		die("--depth cannot exceed %u", MAX_DEPTH);
}