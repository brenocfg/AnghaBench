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
typedef  int /*<<< orphan*/  u64 ;
typedef  enum e820_type { ____Placeholder_e820_type } e820_type ;

/* Variables and functions */
 int _e820__mapped_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e820_table ; 

bool e820__mapped_any(u64 start, u64 end, enum e820_type type)
{
	return _e820__mapped_any(e820_table, start, end, type);
}