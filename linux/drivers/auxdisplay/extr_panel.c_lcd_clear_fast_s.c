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
struct charlcd {int height; int hwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcd_send_serial (char) ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_clear_fast_s(struct charlcd *charlcd)
{
	int pos;

	spin_lock_irq(&pprt_lock);
	for (pos = 0; pos < charlcd->height * charlcd->hwidth; pos++) {
		lcd_send_serial(0x5F);	/* R/W=W, RS=1 */
		lcd_send_serial(' ' & 0x0F);
		lcd_send_serial((' ' >> 4) & 0x0F);
		/* the shortest data takes at least 40 us */
		udelay(40);
	}
	spin_unlock_irq(&pprt_lock);
}