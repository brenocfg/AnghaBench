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
struct TYPE_9__ {int integer; scalar_t__ raw; } ;
struct be {scalar_t__ type; scalar_t__ asnlen; TYPE_1__ data; } ;
struct TYPE_10__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_2__ netdissect_options ;

/* Variables and functions */
 scalar_t__ BE_INT ; 
 scalar_t__ BE_SEQ ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_2__*) ; 
#define  SNMP_VERSION_1 130 
#define  SNMP_VERSION_2 129 
#define  SNMP_VERSION_3 128 
 int /*<<< orphan*/ * SnmpVersion ; 
 int asn1_parse (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__,struct be*) ; 
 int /*<<< orphan*/  asn1_print (TYPE_2__*,struct be*) ; 
 int /*<<< orphan*/  community_print (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 int /*<<< orphan*/  v3msg_print (TYPE_2__*,int /*<<< orphan*/  const*,scalar_t__) ; 

void
snmp_print(netdissect_options *ndo,
           const u_char *np, u_int length)
{
	struct be elem;
	int count = 0;
	int version = 0;

	ND_PRINT((ndo, " "));

	/* initial Sequence */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_SEQ) {
		ND_PRINT((ndo, "[!init SEQ]"));
		asn1_print(ndo, &elem);
		return;
	}
	if ((u_int)count < length)
		ND_PRINT((ndo, "[%d extra after iSEQ]", length - count));
	/* descend */
	length = elem.asnlen;
	np = (const u_char *)elem.data.raw;

	/* Version (INTEGER) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[version!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}

	switch (elem.data.integer) {
	case SNMP_VERSION_1:
	case SNMP_VERSION_2:
	case SNMP_VERSION_3:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo, "{ %s ", SnmpVersion[elem.data.integer]));
		break;
	default:
	        ND_PRINT((ndo, "SNMP [version = %d]", elem.data.integer));
		return;
	}
	version = elem.data.integer;
	length -= count;
	np += count;

	switch (version) {
	case SNMP_VERSION_1:
        case SNMP_VERSION_2:
		community_print(ndo, np, length, version);
		break;
	case SNMP_VERSION_3:
		v3msg_print(ndo, np, length);
		break;
	default:
		ND_PRINT((ndo, "[version = %d]", elem.data.integer));
		break;
	}

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "} "));
	}
}