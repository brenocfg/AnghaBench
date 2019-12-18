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
struct e1000_hw {int dummy; } ;
struct e1000_host_mng_command_header {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_mng_write_cmd_header_generic (struct e1000_hw*,struct e1000_host_mng_command_header*) ; 

s32 e1000_mng_write_cmd_header(struct e1000_hw *hw,
			       struct e1000_host_mng_command_header *hdr)
{
	return e1000_mng_write_cmd_header_generic(hw, hdr);
}