#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; scalar_t__ name; } ;

/* Variables and functions */
 int _RPC_NETPATH ; 
 TYPE_1__* _rpctypelist ; 
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 
 char* strlocase (char const*) ; 

__attribute__((used)) static int
getnettype(const char *nettype)
{
	int i;

	if ((nettype == NULL) || (nettype[0] == 0)) {
		return (_RPC_NETPATH);	/* Default */
	}

#if 0
	nettype = strlocase(nettype);
#endif
	for (i = 0; _rpctypelist[i].name; i++)
		if (strcasecmp(nettype, _rpctypelist[i].name) == 0) {
			return (_rpctypelist[i].type);
		}
	return (_rpctypelist[i].type);
}