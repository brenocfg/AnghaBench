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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int tdsendsignal (struct proc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
pksignal(struct proc *p, int sig, ksiginfo_t *ksi)
{

	return (tdsendsignal(p, NULL, sig, ksi));
}