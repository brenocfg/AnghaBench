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
struct reginit_item {int reg; int val; } ;
struct fs_dev {int dummy; } ;

/* Variables and functions */
 int PHY_CLEARALL ; 
 int PHY_EOF ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  write_phy (struct fs_dev*,int,int) ; 

__attribute__((used)) static int init_phy(struct fs_dev *dev, struct reginit_item *reginit)
{
	int i;

	func_enter ();
	while (reginit->reg != PHY_EOF) {
		if (reginit->reg == PHY_CLEARALL) {
			/* "PHY_CLEARALL means clear all registers. Numregisters is in "val". */
			for (i=0;i<reginit->val;i++) {
				write_phy (dev, i, 0);
			}
		} else {
			write_phy (dev, reginit->reg, reginit->val);
		}
		reginit++;
	}
	func_exit ();
	return 0;
}