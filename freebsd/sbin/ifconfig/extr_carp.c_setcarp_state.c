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
 int CARP_MAXSTATE ; 
 int /*<<< orphan*/ * carp_states ; 
 int carpr_state ; 
 int carpr_vhid ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
setcarp_state(const char *val, int d, int s, const struct afswtch *afp)
{
	int i;

	if (carpr_vhid == -1)
		errx(1, "state requires vhid");

	for (i = 0; i <= CARP_MAXSTATE; i++)
		if (strcasecmp(carp_states[i], val) == 0) {
			carpr_state = i;
			return;
		}

	errx(1, "unknown state");
}