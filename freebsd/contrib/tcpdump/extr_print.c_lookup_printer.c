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
struct printer {int type; int /*<<< orphan*/ * f; } ;
typedef  int /*<<< orphan*/ * if_printer ;

/* Variables and functions */
 int DLT_PKTAP ; 
 int DLT_USER2 ; 
 struct printer* printers ; 

if_printer
lookup_printer(int type)
{
	const struct printer *p;

	for (p = printers; p->f; ++p)
		if (type == p->type)
			return p->f;

#if defined(DLT_USER2) && defined(DLT_PKTAP)
	/*
	 * Apple incorrectly chose to use DLT_USER2 for their PKTAP
	 * header.
	 *
	 * We map DLT_PKTAP, whether it's DLT_USER2 as it is on Darwin-
	 * based OSes or the same value as LINKTYPE_PKTAP as it is on
	 * other OSes, to LINKTYPE_PKTAP, so files written with
	 * this version of libpcap for a DLT_PKTAP capture have a link-
	 * layer header type of LINKTYPE_PKTAP.
	 *
	 * However, files written on OS X Mavericks for a DLT_PKTAP
	 * capture have a link-layer header type of LINKTYPE_USER2.
	 * If we don't have a printer for DLT_USER2, and type is
	 * DLT_USER2, we look up the printer for DLT_PKTAP and use
	 * that.
	 */
	if (type == DLT_USER2) {
		for (p = printers; p->f; ++p)
			if (DLT_PKTAP == p->type)
				return p->f;
	}
#endif

	return NULL;
	/* NOTREACHED */
}