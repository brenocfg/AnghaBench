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
typedef  size_t u_int ;
struct ssh {int /*<<< orphan*/ ** dispatch; } ;
typedef  int /*<<< orphan*/  dispatch_fn ;

/* Variables and functions */
 size_t DISPATCH_MAX ; 

void
ssh_dispatch_init(struct ssh *ssh, dispatch_fn *dflt)
{
	u_int i;
	for (i = 0; i < DISPATCH_MAX; i++)
		ssh->dispatch[i] = dflt;
}