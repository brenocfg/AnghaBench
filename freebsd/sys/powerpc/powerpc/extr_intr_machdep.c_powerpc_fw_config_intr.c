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
struct powerpc_intr {int fwcode; int /*<<< orphan*/  pol; int /*<<< orphan*/  trig; int /*<<< orphan*/  intline; int /*<<< orphan*/ * pic; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_INVALID ; 
 int /*<<< orphan*/  PIC_CONFIG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC_TRANSLATE_CODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cold ; 
 struct powerpc_intr* intr_lookup (int) ; 

int
powerpc_fw_config_intr(int irq, int sense_code)
{
	struct powerpc_intr *i;

	i = intr_lookup(irq);
	if (i == NULL)
		return (ENOMEM);

	i->trig = INTR_TRIGGER_INVALID;
	i->pol = INTR_POLARITY_CONFORM;
	i->fwcode = sense_code;

	if (!cold && i->pic != NULL) {
		PIC_TRANSLATE_CODE(i->pic, i->intline, i->fwcode, &i->trig,
		    &i->pol);
		PIC_CONFIG(i->pic, i->intline, i->trig, i->pol);
	}

	return (0);
}