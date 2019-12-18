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
struct irq_data {int irq; } ;

/* Variables and functions */
 int* enat_cpld ; 
 int /*<<< orphan*/  iounmap (int*) ; 

__attribute__((used)) static void atari_ethernat_shutdown(struct irq_data *data)
{
	int enat_num = 140 - data->irq + 1;
	if (enat_cpld) {
		*enat_cpld &= ~(1 << enat_num);
		iounmap(enat_cpld);
		enat_cpld = NULL;
	}
}