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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ CC_FIRST_CPP_KEY_SLOT ; 

__attribute__((used)) static u8 cc_slot_to_cpp_key(u8 slot_num)
{
	return (slot_num - CC_FIRST_CPP_KEY_SLOT);
}