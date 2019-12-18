#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct termp {scalar_t__ type; TYPE_1__* ps; } ;
struct TYPE_2__ {int flags; scalar_t__ psrow; scalar_t__ lastrow; } ;

/* Variables and functions */
 int PS_INLINE ; 
 scalar_t__ TERMTYPE_PS ; 
 int /*<<< orphan*/  ps_printf (struct termp*,char*) ; 

__attribute__((used)) static void
ps_pclose(struct termp *p)
{

	/*
	 * Spit out that we're exiting a word context (this is a
	 * "partial close" because we don't check the last-char buffer
	 * or anything).
	 */

	if ( ! (PS_INLINE & p->ps->flags))
		return;

	if (TERMTYPE_PS != p->type)
		ps_printf(p, ") Tj\nET\n");
	else if (p->ps->psrow == p->ps->lastrow)
		ps_printf(p, ")c\n");
	else {
		ps_printf(p, ")s\n");
		p->ps->lastrow = p->ps->psrow;
	}

	p->ps->flags &= ~PS_INLINE;
}