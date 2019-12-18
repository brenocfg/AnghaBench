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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSABET_BCR_IRDA_FSEL ; 
 int /*<<< orphan*/  ASSABET_BCR_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSABET_BCR_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assabet_irda_set_speed(struct device *dev, unsigned int speed)
{
	if (speed < 4000000)
		ASSABET_BCR_clear(ASSABET_BCR_IRDA_FSEL);
	else
		ASSABET_BCR_set(ASSABET_BCR_IRDA_FSEL);
}