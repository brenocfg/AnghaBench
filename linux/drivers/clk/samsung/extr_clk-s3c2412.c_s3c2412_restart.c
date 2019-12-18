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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLKSRC ; 
 int NOTIFY_DONE ; 
 scalar_t__ SWRST ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static int s3c2412_restart(struct notifier_block *this,
			   unsigned long mode, void *cmd)
{
	/* errata "Watch-dog/Software Reset Problem" specifies that
	 * this reset must be done with the SYSCLK sourced from
	 * EXTCLK instead of FOUT to avoid a glitch in the reset
	 * mechanism.
	 *
	 * See the watchdog section of the S3C2412 manual for more
	 * information on this fix.
	 */

	__raw_writel(0x00, reg_base + CLKSRC);
	__raw_writel(0x533C2412, reg_base + SWRST);
	return NOTIFY_DONE;
}