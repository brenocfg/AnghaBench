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
struct pit_data {int cycle; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PIT_MR ; 
 int AT91_PIT_PITEN ; 
 int /*<<< orphan*/  AT91_PIT_PIVR ; 
 scalar_t__ PIT_CPIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pit_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pit_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91sam926x_pit_reset(struct pit_data *data)
{
	/* Disable timer and irqs */
	pit_write(data->base, AT91_PIT_MR, 0);

	/* Clear any pending interrupts, wait for PIT to stop counting */
	while (PIT_CPIV(pit_read(data->base, AT91_PIT_PIVR)) != 0)
		cpu_relax();

	/* Start PIT but don't enable IRQ */
	pit_write(data->base, AT91_PIT_MR,
		  (data->cycle - 1) | AT91_PIT_PITEN);
}