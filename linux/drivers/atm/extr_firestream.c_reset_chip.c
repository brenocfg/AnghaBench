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
struct fs_dev {int dummy; } ;

/* Variables and functions */
 int FP_CNF (int /*<<< orphan*/ ) ; 
 int FP_CNT (int /*<<< orphan*/ ) ; 
 int FP_CTU (int /*<<< orphan*/ ) ; 
 int FP_EA (int /*<<< orphan*/ ) ; 
 int FP_SA (int /*<<< orphan*/ ) ; 
 int FS50_NR_CHANNELS ; 
 int FS_NR_FREE_POOLS ; 
 scalar_t__ IS_FS50 (struct fs_dev*) ; 
 int /*<<< orphan*/  RXB_FP (int) ; 
 int SARMODE0 ; 
 int SARMODE0_SRTS0 ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int,int) ; 

__attribute__((used)) static void reset_chip (struct fs_dev *dev)
{
	int i;

	write_fs (dev, SARMODE0, SARMODE0_SRTS0);

	/* Undocumented delay */
	udelay (128);

	/* The "internal registers are documented to all reset to zero, but 
	   comments & code in the Windows driver indicates that the pools are
	   NOT reset. */
	for (i=0;i < FS_NR_FREE_POOLS;i++) {
		write_fs (dev, FP_CNF (RXB_FP(i)), 0);
		write_fs (dev, FP_SA  (RXB_FP(i)), 0);
		write_fs (dev, FP_EA  (RXB_FP(i)), 0);
		write_fs (dev, FP_CNT (RXB_FP(i)), 0);
		write_fs (dev, FP_CTU (RXB_FP(i)), 0);
	}

	/* The same goes for the match channel registers, although those are
	   NOT documented that way in the Windows driver. -- REW */
	/* The Windows driver DOES write 0 to these registers somewhere in
	   the init sequence. However, a small hardware-feature, will
	   prevent reception of data on VPI/VCI = 0/0 (Unless the channel
	   allocated happens to have no disabled channels that have a lower
	   number. -- REW */

	/* Clear the match channel registers. */
	if (IS_FS50 (dev)) {
		for (i=0;i<FS50_NR_CHANNELS;i++) {
			write_fs (dev, 0x200 + i * 4, -1);
		}
	}
}