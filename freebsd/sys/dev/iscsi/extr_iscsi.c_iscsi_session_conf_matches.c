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
struct iscsi_session_conf {char* isc_target; char* isc_target_addr; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool
iscsi_session_conf_matches(unsigned int id1, const struct iscsi_session_conf *c1,
    unsigned int id2, const struct iscsi_session_conf *c2)
{

	if (id2 != 0 && id2 != id1)
		return (false);
	if (c2->isc_target[0] != '\0' &&
	    strcmp(c1->isc_target, c2->isc_target) != 0)
		return (false);
	if (c2->isc_target_addr[0] != '\0' &&
	    strcmp(c1->isc_target_addr, c2->isc_target_addr) != 0)
		return (false);
	return (true);
}