#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int /*<<< orphan*/  ndo_bflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static char *
as_printf(netdissect_options *ndo,
          char *str, int size, u_int asnum)
{
	if (!ndo->ndo_bflag || asnum <= 0xFFFF) {
		snprintf(str, size, "%u", asnum);
	} else {
		snprintf(str, size, "%u.%u", asnum >> 16, asnum & 0xFFFF);
	}
	return str;
}