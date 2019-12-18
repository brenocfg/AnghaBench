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
struct roff {int format; int options; char control; char escape; } ;

/* Variables and functions */
 int MPARSE_MAN ; 
 int MPARSE_MDOC ; 
 int /*<<< orphan*/  roff_free1 (struct roff*) ; 
 scalar_t__ roffce_lines ; 
 int /*<<< orphan*/ * roffce_node ; 
 scalar_t__ roffit_lines ; 
 int /*<<< orphan*/ * roffit_macro ; 

void
roff_reset(struct roff *r)
{
	roff_free1(r);
	r->format = r->options & (MPARSE_MDOC | MPARSE_MAN);
	r->control = '\0';
	r->escape = '\\';
	roffce_lines = 0;
	roffce_node = NULL;
	roffit_lines = 0;
	roffit_macro = NULL;
}