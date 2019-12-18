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

/* Variables and functions */
 int /*<<< orphan*/  _PATH_BT_PROTOCOLS ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int proto_stayopen ; 
 int /*<<< orphan*/ * protof ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

void
bt_setprotoent(int stayopen)
{
	if (protof == NULL)
		protof = fopen(_PATH_BT_PROTOCOLS, "r");
	else
		rewind(protof);

	proto_stayopen = stayopen;
}