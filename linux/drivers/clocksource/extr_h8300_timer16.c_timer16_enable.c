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
struct timer16_priv {int cs_enabled; scalar_t__ mapcommon; int /*<<< orphan*/  enb; int /*<<< orphan*/  ovie; scalar_t__ mapbase; scalar_t__ total_cycles; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCNT ; 
 scalar_t__ TCR ; 
 scalar_t__ TISRC ; 
 scalar_t__ TSTR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bset (int /*<<< orphan*/ ,scalar_t__) ; 
 struct timer16_priv* cs_to_priv (struct clocksource*) ; 
 int /*<<< orphan*/  iowrite16be (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 

__attribute__((used)) static int timer16_enable(struct clocksource *cs)
{
	struct timer16_priv *p = cs_to_priv(cs);

	WARN_ON(p->cs_enabled);

	p->total_cycles = 0;
	iowrite16be(0x0000, p->mapbase + TCNT);
	iowrite8(0x83, p->mapbase + TCR);
	bset(p->ovie, p->mapcommon + TISRC);
	bset(p->enb, p->mapcommon + TSTR);

	p->cs_enabled = true;
	return 0;
}