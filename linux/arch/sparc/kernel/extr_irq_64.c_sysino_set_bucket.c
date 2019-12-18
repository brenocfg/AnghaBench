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
struct irq_handler_data {int /*<<< orphan*/  dev_ino; int /*<<< orphan*/  dev_handle; } ;
struct ino_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __pa (struct ino_bucket*) ; 
 int /*<<< orphan*/  bucket_set_irq (int /*<<< orphan*/ ,unsigned int) ; 
 struct irq_handler_data* irq_get_handler_data (unsigned int) ; 
 struct ino_bucket* ivector_table ; 
 unsigned long nr_ivec ; 
 unsigned long sun4v_devino_to_sysino (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysino_set_bucket(unsigned int irq)
{
	struct irq_handler_data *ihd = irq_get_handler_data(irq);
	struct ino_bucket *bucket;
	unsigned long sysino;

	sysino = sun4v_devino_to_sysino(ihd->dev_handle, ihd->dev_ino);
	BUG_ON(sysino >= nr_ivec);
	bucket = &ivector_table[sysino];
	bucket_set_irq(__pa(bucket), irq);
}