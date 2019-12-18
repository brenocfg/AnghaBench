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
struct gdbcons {int npending; int /*<<< orphan*/  flush; } ;
struct consdev {struct gdbcons* cn_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 struct gdbcons state ; 

__attribute__((used)) static void
gdb_cninit(struct consdev *cp)
{
	struct gdbcons *c = &state;

	/* setup tx buffer and callout */
	if (c->npending == -1) {
		c->npending = 0;
		callout_init(&c->flush, 1);
		cp->cn_arg = c;
	}
}