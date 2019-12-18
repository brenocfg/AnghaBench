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
struct pd_unit {int dummy; } ;

/* Variables and functions */
 int DRIVE (struct pd_unit*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_reg (struct pd_unit*,int,int) ; 

__attribute__((used)) static void pd_send_command(struct pd_unit *disk, int n, int s, int h, int c0, int c1, int func)
{
	write_reg(disk, 6, DRIVE(disk) + h);
	write_reg(disk, 1, 0);		/* the IDE task file */
	write_reg(disk, 2, n);
	write_reg(disk, 3, s);
	write_reg(disk, 4, c0);
	write_reg(disk, 5, c1);
	write_reg(disk, 7, func);

	udelay(1);
}