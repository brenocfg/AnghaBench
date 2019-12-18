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
struct afswtch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCDIFPHYADDR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  ifr ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
deletetunnel(const char *vname, int param, int s, const struct afswtch *afp)
{

	if (ioctl(s, SIOCDIFPHYADDR, &ifr) < 0)
		err(1, "SIOCDIFPHYADDR");
}