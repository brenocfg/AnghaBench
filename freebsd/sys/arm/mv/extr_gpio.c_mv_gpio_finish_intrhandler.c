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
struct mv_gpio_pindev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct mv_gpio_pindev*,int /*<<< orphan*/ ) ; 

void
mv_gpio_finish_intrhandler(struct mv_gpio_pindev *s)
{
	/* When we acheive full interrupt support
	 * This function will be opposite to
	 * mv_gpio_setup_intrhandler
	 */

	/* Now it exists only to remind that
	 * there should be place to free mv_gpio_pindev
	 * allocated by mv_gpio_setup_intrhandler
	 */
	free(s, M_DEVBUF);
}