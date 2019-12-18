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
struct pata_icside_state {scalar_t__ irq_port; } ;
struct expansion_card {struct pata_icside_state* irq_data; } ;

/* Variables and functions */
 scalar_t__ ICS_ARCIN_V6_INTRSTAT_1 ; 
 scalar_t__ ICS_ARCIN_V6_INTRSTAT_2 ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int pata_icside_irqpending_arcin_v6(struct expansion_card *ec)
{
	struct pata_icside_state *state = ec->irq_data;

	return readb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_1) & 1 ||
	       readb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_2) & 1;
}