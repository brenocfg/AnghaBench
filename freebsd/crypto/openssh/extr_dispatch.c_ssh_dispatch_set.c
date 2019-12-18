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
struct ssh {int /*<<< orphan*/ ** dispatch; } ;
typedef  int /*<<< orphan*/  dispatch_fn ;

/* Variables and functions */

void
ssh_dispatch_set(struct ssh *ssh, int type, dispatch_fn *fn)
{
	ssh->dispatch[type] = fn;
}