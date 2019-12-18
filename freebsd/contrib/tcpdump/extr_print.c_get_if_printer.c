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
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*,int) ;} ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/ * if_printer ;

/* Variables and functions */
 int /*<<< orphan*/ * lookup_printer (int) ; 
 char* pcap_datalink_val_to_name (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*,int) ; 

if_printer
get_if_printer(netdissect_options *ndo, int type)
{
	const char *dltname;
	if_printer printer;

	printer = lookup_printer(type);
	if (printer == NULL) {
		dltname = pcap_datalink_val_to_name(type);
		if (dltname != NULL)
			(*ndo->ndo_error)(ndo,
					  "packet printing is not supported for link type %s: use -w",
					  dltname);
		else
			(*ndo->ndo_error)(ndo,
					  "packet printing is not supported for link type %d: use -w", type);
	}
	return printer;
}