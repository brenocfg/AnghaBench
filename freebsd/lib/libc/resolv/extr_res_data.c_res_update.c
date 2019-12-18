#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  ns_updrec ;
struct TYPE_5__ {unsigned int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 unsigned int RES_INIT ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ _res ; 
 int res_init () ; 
 int res_nupdate (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
res_update(ns_updrec *rrecp_in) {
	res_state statp = &_res;
	if ((statp->options & RES_INIT) == 0U && res_init() == -1) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}

	return (res_nupdate(statp, rrecp_in, NULL));
}