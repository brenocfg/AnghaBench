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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct udl_cmd_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udl_cmd_write_reg_1 (struct udl_cmd_buf*,scalar_t__,int) ; 

__attribute__((used)) static void
udl_cmd_write_reg_3(struct udl_cmd_buf *cb, uint8_t reg, uint32_t val)
{

	udl_cmd_write_reg_1(cb, reg + 0, (val >> 16) & 0xff);
	udl_cmd_write_reg_1(cb, reg + 1, (val >> 8) & 0xff);
	udl_cmd_write_reg_1(cb, reg + 2, (val >> 0) & 0xff);
}