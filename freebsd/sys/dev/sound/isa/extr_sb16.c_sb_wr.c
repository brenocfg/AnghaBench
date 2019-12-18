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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sb_info {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sb_wr(struct sb_info *sb, int reg, u_int8_t val)
{
	port_wr(sb->io_base, reg, val);
}