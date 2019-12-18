#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int integer; } ;
struct be {scalar_t__ type; TYPE_1__ data; } ;
struct TYPE_9__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_2__ netdissect_options ;

/* Variables and functions */
 scalar_t__ BE_INT ; 
 int /*<<< orphan*/  DECODE_ErrorStatus (int) ; 
 scalar_t__ GETBULKREQ ; 
 scalar_t__ GETNEXTREQ ; 
 scalar_t__ GETREQ ; 
 scalar_t__ INFORMREQ ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_2__*) ; 
 scalar_t__ REPORT ; 
 scalar_t__ SETREQ ; 
 scalar_t__ V2TRAP ; 
 int asn1_parse (TYPE_2__*,int /*<<< orphan*/  const*,int,struct be*) ; 
 int /*<<< orphan*/  asn1_print (TYPE_2__*,struct be*) ; 
 int /*<<< orphan*/  varbind_print (TYPE_2__*,scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
snmppdu_print(netdissect_options *ndo,
              u_short pduid, const u_char *np, u_int length)
{
	struct be elem;
	int count = 0, error_status;

	/* reqId (Integer) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[reqId!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	if (ndo->ndo_vflag)
		ND_PRINT((ndo, "R=%d ", elem.data.integer));
	length -= count;
	np += count;

	/* errorStatus (Integer) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[errorStatus!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	error_status = 0;
	if ((pduid == GETREQ || pduid == GETNEXTREQ || pduid == SETREQ
	    || pduid == INFORMREQ || pduid == V2TRAP || pduid == REPORT)
	    && elem.data.integer != 0) {
		char errbuf[20];
		ND_PRINT((ndo, "[errorStatus(%s)!=0]",
			DECODE_ErrorStatus(elem.data.integer)));
	} else if (pduid == GETBULKREQ) {
		ND_PRINT((ndo, " N=%d", elem.data.integer));
	} else if (elem.data.integer != 0) {
		char errbuf[20];
		ND_PRINT((ndo, " %s", DECODE_ErrorStatus(elem.data.integer)));
		error_status = elem.data.integer;
	}
	length -= count;
	np += count;

	/* errorIndex (Integer) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[errorIndex!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	if ((pduid == GETREQ || pduid == GETNEXTREQ || pduid == SETREQ
	    || pduid == INFORMREQ || pduid == V2TRAP || pduid == REPORT)
	    && elem.data.integer != 0)
		ND_PRINT((ndo, "[errorIndex(%d)!=0]", elem.data.integer));
	else if (pduid == GETBULKREQ)
		ND_PRINT((ndo, " M=%d", elem.data.integer));
	else if (elem.data.integer != 0) {
		if (!error_status)
			ND_PRINT((ndo, "[errorIndex(%d) w/o errorStatus]", elem.data.integer));
		else
			ND_PRINT((ndo, "@%d", elem.data.integer));
	} else if (error_status) {
		ND_PRINT((ndo, "[errorIndex==0]"));
	}
	length -= count;
	np += count;

	varbind_print(ndo, pduid, np, length);
	return;
}