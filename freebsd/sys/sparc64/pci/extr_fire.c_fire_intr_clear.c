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
struct intr_vector {struct fire_icarg* iv_icarg; } ;
struct fire_icarg {int /*<<< orphan*/  fica_clr; int /*<<< orphan*/  fica_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTCLR_IDLE ; 

__attribute__((used)) static void
fire_intr_clear(void *arg)
{
	struct intr_vector *iv;
	struct fire_icarg *fica;

	iv = arg;
	fica = iv->iv_icarg;
	FIRE_PCI_WRITE_8(fica->fica_sc, fica->fica_clr, INTCLR_IDLE);
}