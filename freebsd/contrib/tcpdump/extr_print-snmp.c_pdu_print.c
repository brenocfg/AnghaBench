#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {scalar_t__ raw; } ;
struct be {scalar_t__ type; scalar_t__ asnlen; int id; TYPE_1__ data; } ;
struct TYPE_10__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_2__ netdissect_options ;

/* Variables and functions */
 scalar_t__ BE_PDU ; 
#define  GETBULKREQ 136 
#define  GETNEXTREQ 135 
#define  GETREQ 134 
#define  GETRESP 133 
#define  INFORMREQ 132 
 int /*<<< orphan*/  ND_PRINT (TYPE_2__*) ; 
#define  REPORT 131 
#define  SETREQ 130 
 int SNMP_VERSION_1 ; 
 int SNMP_VERSION_2 ; 
#define  TRAP 129 
#define  V2TRAP 128 
 int asn1_parse (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__,struct be*) ; 
 scalar_t__ asn1_print (TYPE_2__*,struct be*) ; 
 int /*<<< orphan*/  snmppdu_print (TYPE_2__*,int,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  trappdu_print (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void
pdu_print(netdissect_options *ndo,
          const u_char *np, u_int length, int version)
{
	struct be pdu;
	int count = 0;

	/* PDU (Context) */
	if ((count = asn1_parse(ndo, np, length, &pdu)) < 0)
		return;
	if (pdu.type != BE_PDU) {
		ND_PRINT((ndo, "[no PDU]"));
		return;
	}
	if ((u_int)count < length)
		ND_PRINT((ndo, "[%d extra after PDU]", length - count));
	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "{ "));
	}
	if (asn1_print(ndo, &pdu) < 0)
		return;
	ND_PRINT((ndo, " "));
	/* descend into PDU */
	length = pdu.asnlen;
	np = (const u_char *)pdu.data.raw;

	if (version == SNMP_VERSION_1 &&
	    (pdu.id == GETBULKREQ || pdu.id == INFORMREQ ||
	     pdu.id == V2TRAP || pdu.id == REPORT)) {
	        ND_PRINT((ndo, "[v2 PDU in v1 message]"));
		return;
	}

	if (version == SNMP_VERSION_2 && pdu.id == TRAP) {
		ND_PRINT((ndo, "[v1 PDU in v2 message]"));
		return;
	}

	switch (pdu.id) {
	case TRAP:
		trappdu_print(ndo, np, length);
		break;
	case GETREQ:
	case GETNEXTREQ:
	case GETRESP:
	case SETREQ:
	case GETBULKREQ:
	case INFORMREQ:
	case V2TRAP:
	case REPORT:
		snmppdu_print(ndo, pdu.id, np, length);
		break;
	}

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, " } "));
	}
}