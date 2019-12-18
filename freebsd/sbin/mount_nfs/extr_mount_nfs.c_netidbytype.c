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
struct nc_protos {char const* netid; int af; int sotype; } ;

/* Variables and functions */
 struct nc_protos* nc_protos ; 

__attribute__((used)) static const char *
netidbytype(int af, int sotype)
{
	struct nc_protos *p;

	for (p = nc_protos; p->netid != NULL; p++) {
		if (af != p->af || sotype != p->sotype)
			continue;
		return (p->netid);
	}
	return (NULL);
}