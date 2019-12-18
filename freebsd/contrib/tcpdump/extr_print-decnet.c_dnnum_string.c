#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int AREAMASK ; 
 int AREASHIFT ; 
 int NODEMASK ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

const char *
dnnum_string(netdissect_options *ndo, u_short dnaddr)
{
	char *str;
	size_t siz;
	int area = (u_short)(dnaddr & AREAMASK) >> AREASHIFT;
	int node = dnaddr & NODEMASK;

	str = (char *)malloc(siz = sizeof("00.0000"));
	if (str == NULL)
		(*ndo->ndo_error)(ndo, "dnnum_string: malloc");
	snprintf(str, siz, "%d.%d", area, node);
	return(str);
}