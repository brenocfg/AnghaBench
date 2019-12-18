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
struct pfsync_state {int dummy; } ;
struct pf_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfsync_state_export (struct pfsync_state*,struct pf_state*) ; 

__attribute__((used)) static void
pfsync_out_state(struct pf_state *st, void *buf)
{
	struct pfsync_state *sp = buf;

	pfsync_state_export(sp, st);
}