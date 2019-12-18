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
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  carpr_advbase ; 
 int carpr_vhid ; 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static void
setcarp_advbase(const char *val, int d, int s, const struct afswtch *afp)
{

	if (carpr_vhid == -1)
		errx(1, "advbase requires vhid");

	carpr_advbase = atoi(val);
}