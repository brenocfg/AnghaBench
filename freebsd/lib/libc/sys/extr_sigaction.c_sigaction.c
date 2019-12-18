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
struct sigaction {int dummy; } ;

/* Variables and functions */
 size_t INTERPOS_sigaction ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,struct sigaction const*,struct sigaction*) ; 

int
sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{

	return (((int (*)(int, const struct sigaction *, struct sigaction *))
	    __libc_interposing[INTERPOS_sigaction])(sig, act, oact));
}