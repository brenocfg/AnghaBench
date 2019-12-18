#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ chan; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1SR (int /*<<< orphan*/ ) ; 
 unsigned char E1SR_E0_IRQ1 ; 
 unsigned char E1SR_E1_IRQ1 ; 
 unsigned char E1SR_SCC_IRQ ; 
 int /*<<< orphan*/  ct_e1timer_interrupt (scalar_t__) ; 
 int /*<<< orphan*/  ct_scc_interrupt (TYPE_1__*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_e1_interrupt (ct_board_t *b)
{
	unsigned char sr;

	sr = inb (E1SR(b->port));

	if (sr & E1SR_SCC_IRQ) ct_scc_interrupt (b);
	if (sr & E1SR_E0_IRQ1) ct_e1timer_interrupt (b->chan + 0);
	if (sr & E1SR_E1_IRQ1) ct_e1timer_interrupt (b->chan + 1);
}