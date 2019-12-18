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
struct intrupt {scalar_t__ inuse; int /*<<< orphan*/  new_pmhandler; int /*<<< orphan*/  old_pmhandler; int /*<<< orphan*/  new_rmhandler; int /*<<< orphan*/  old_rmhandler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICU_MASK ; 
 int /*<<< orphan*/  _go32_dpmi_free_iret_wrapper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_free_real_mode_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_protected_mode_interrupt_vector (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_real_mode_interrupt_vector (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable () ; 
 int /*<<< orphan*/  enable () ; 
 unsigned char icu_oldmask ; 
 unsigned char inportb (int /*<<< orphan*/ ) ; 
 struct intrupt* intrupts ; 
 int /*<<< orphan*/  outportb (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
dos_unhookirq (struct intrupt *intr)
{
  unsigned int irq, vec;
  unsigned char mask;

  irq = intr - intrupts;
  vec = 0x08 + irq;

  /* restore old interrupt mask bit */
  mask = 1 << irq;
  disable ();
  outportb (ICU_MASK, inportb (ICU_MASK) | (mask & icu_oldmask));
  enable ();

  /* remove real mode handler */
  _go32_dpmi_set_real_mode_interrupt_vector (vec, &intr->old_rmhandler);
  _go32_dpmi_free_real_mode_callback (&intr->new_rmhandler);

  /* remove protected mode handler */
  _go32_dpmi_set_protected_mode_interrupt_vector (vec, &intr->old_pmhandler);
  _go32_dpmi_free_iret_wrapper (&intr->new_pmhandler);
  intr->inuse = 0;
}