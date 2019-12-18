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
typedef  int u16 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  ext_int_hash ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static inline int ext_hash(u16 code)
{
	BUILD_BUG_ON(!is_power_of_2(ARRAY_SIZE(ext_int_hash)));

	return (code + (code >> 9)) & (ARRAY_SIZE(ext_int_hash) - 1);
}