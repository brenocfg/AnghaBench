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
typedef  int /*<<< orphan*/  u_int ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_POLARITY_CONFORM ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_POLARITY_LOW ; 
 int INTR_TRIGGER_CONFORM ; 
 int INTR_TRIGGER_EDGE ; 
 int INTR_TRIGGER_LEVEL ; 

__attribute__((used)) static void
atpic_ofw_translate_code(device_t dev, u_int irq, int code,
    enum intr_trigger *trig, enum intr_polarity *pol)
{
	switch (code) {
	case 0:
		/* Active L level */
		*trig = INTR_TRIGGER_LEVEL;
		*pol = INTR_POLARITY_LOW;
		break;
	case 1:
		/* Active H level */
		*trig = INTR_TRIGGER_LEVEL;
		*pol = INTR_POLARITY_HIGH;
		break;
	case 2:
		/* H to L edge */
		*trig = INTR_TRIGGER_EDGE;
		*pol = INTR_POLARITY_LOW;
		break;
	case 3:
		/* L to H edge */
		*trig = INTR_TRIGGER_EDGE;
		*pol = INTR_POLARITY_HIGH;
		break;
	default:
		*trig = INTR_TRIGGER_CONFORM;
		*pol = INTR_POLARITY_CONFORM;
	}
}