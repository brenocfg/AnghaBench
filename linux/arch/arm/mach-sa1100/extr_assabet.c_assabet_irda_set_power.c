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
#define  ASSABET_BCR_IRDA_MD0 129 
#define  ASSABET_BCR_IRDA_MD1 128 
 int /*<<< orphan*/  ASSABET_BCR_frob (unsigned int const,unsigned int) ; 

__attribute__((used)) static int assabet_irda_set_power(struct device *dev, unsigned int state)
{
	static unsigned int bcr_state[4] = {
		ASSABET_BCR_IRDA_MD0,
		ASSABET_BCR_IRDA_MD1|ASSABET_BCR_IRDA_MD0,
		ASSABET_BCR_IRDA_MD1,
		0
	};

	if (state < 4)
		ASSABET_BCR_frob(ASSABET_BCR_IRDA_MD1 | ASSABET_BCR_IRDA_MD0,
				 bcr_state[state]);
	return 0;
}