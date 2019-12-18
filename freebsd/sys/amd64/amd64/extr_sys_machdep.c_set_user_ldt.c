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
struct mdproc {int /*<<< orphan*/  md_ldt_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUSERLDT_SEL ; 
 int /*<<< orphan*/ * PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  ldt ; 
 int /*<<< orphan*/  lldt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_user_ldt(struct mdproc *mdp)
{

	*PCPU_GET(ldt) = mdp->md_ldt_sd;
	lldt(GSEL(GUSERLDT_SEL, SEL_KPL));
}