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
struct afswtch {scalar_t__ af_af; int /*<<< orphan*/  (* af_getaddr ) (char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  RIDADDR ; 
 int clearaddr ; 
 scalar_t__ doalias ; 
 int /*<<< orphan*/  setaddr ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setifaddr(const char *addr, int param, int s, const struct afswtch *afp)
{
	if (afp->af_getaddr == NULL)
		return;
	/*
	 * Delay the ioctl to set the interface addr until flags are all set.
	 * The address interpretation may depend on the flags,
	 * and the flags may change when the address is set.
	 */
	setaddr++;
	if (doalias == 0 && afp->af_af != AF_LINK)
		clearaddr = 1;
	afp->af_getaddr(addr, (doalias >= 0 ? ADDR : RIDADDR));
}