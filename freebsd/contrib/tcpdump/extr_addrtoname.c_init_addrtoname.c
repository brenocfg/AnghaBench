#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_8__ {scalar_t__ ndo_nflag; scalar_t__ ndo_fflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 void* f_localnet ; 
 void* f_netmask ; 
 int /*<<< orphan*/  init_eprotoarray (TYPE_1__*) ; 
 int /*<<< orphan*/  init_etherarray (TYPE_1__*) ; 
 int /*<<< orphan*/  init_ipxsaparray (TYPE_1__*) ; 
 int /*<<< orphan*/  init_protoidarray (TYPE_1__*) ; 
 int /*<<< orphan*/  init_servarray (TYPE_1__*) ; 

void
init_addrtoname(netdissect_options *ndo, uint32_t localnet, uint32_t mask)
{
	if (ndo->ndo_fflag) {
		f_localnet = localnet;
		f_netmask = mask;
	}
	if (ndo->ndo_nflag)
		/*
		 * Simplest way to suppress names.
		 */
		return;

	init_etherarray(ndo);
	init_servarray(ndo);
	init_eprotoarray(ndo);
	init_protoidarray(ndo);
	init_ipxsaparray(ndo);
}