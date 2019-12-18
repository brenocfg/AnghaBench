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
struct em_sti_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_INTENCLR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_sti_write (struct em_sti_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void em_sti_disable(struct em_sti_priv *p)
{
	/* mask interrupts */
	em_sti_write(p, STI_INTENCLR, 3);

	/* stop clock */
	clk_disable(p->clk);
}