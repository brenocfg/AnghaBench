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
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_9__ {int* str; int integer; scalar_t__ raw; } ;
struct be {scalar_t__ type; int asnlen; TYPE_1__ data; } ;
struct TYPE_10__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_2__ netdissect_options ;

/* Variables and functions */
 scalar_t__ BE_INT ; 
 scalar_t__ BE_SEQ ; 
 scalar_t__ BE_STR ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_2__*) ; 
 int asn1_parse (TYPE_2__*,int const*,int,struct be*) ; 
 int /*<<< orphan*/  asn1_print (TYPE_2__*,struct be*) ; 
 int /*<<< orphan*/  scopedpdu_print (TYPE_2__*,int const*,int,int) ; 
 int /*<<< orphan*/  usm_print (TYPE_2__*,int*,int) ; 

__attribute__((used)) static void
v3msg_print(netdissect_options *ndo,
            const u_char *np, u_int length)
{
	struct be elem;
	int count = 0;
	u_char flags;
	int model;
	const u_char *xnp = np;
	int xlength = length;

	/* Sequence */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_SEQ) {
		ND_PRINT((ndo, "[!message]"));
		asn1_print(ndo, &elem);
		return;
	}
	length = elem.asnlen;
	np = (const u_char *)elem.data.raw;

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "{ "));
	}

	/* msgID (INTEGER) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[msgID!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	length -= count;
	np += count;

	/* msgMaxSize (INTEGER) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[msgMaxSize!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	length -= count;
	np += count;

	/* msgFlags (OCTET STRING) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		ND_PRINT((ndo, "[msgFlags!=STR]"));
		asn1_print(ndo, &elem);
		return;
	}
	if (elem.asnlen != 1) {
		ND_PRINT((ndo, "[msgFlags size %d]", elem.asnlen));
		return;
	}
	flags = elem.data.str[0];
	if (flags != 0x00 && flags != 0x01 && flags != 0x03
	    && flags != 0x04 && flags != 0x05 && flags != 0x07) {
		ND_PRINT((ndo, "[msgFlags=0x%02X]", flags));
		return;
	}
	length -= count;
	np += count;

	ND_PRINT((ndo, "F=%s%s%s ",
	          flags & 0x01 ? "a" : "",
	          flags & 0x02 ? "p" : "",
	          flags & 0x04 ? "r" : ""));

	/* msgSecurityModel (INTEGER) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		ND_PRINT((ndo, "[msgSecurityModel!=INT]"));
		asn1_print(ndo, &elem);
		return;
	}
	model = elem.data.integer;
	length -= count;
	np += count;

	if ((u_int)count < length)
		ND_PRINT((ndo, "[%d extra after message SEQ]", length - count));

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "} "));
	}

	if (model == 3) {
	    if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "{ USM "));
	    }
	} else {
	    ND_PRINT((ndo, "[security model %d]", model));
            return;
	}

	np = xnp + (np - xnp);
	length = xlength - (np - xnp);

	/* msgSecurityParameters (OCTET STRING) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		ND_PRINT((ndo, "[msgSecurityParameters!=STR]"));
		asn1_print(ndo, &elem);
		return;
	}
	length -= count;
	np += count;

	if (model == 3) {
	    usm_print(ndo, elem.data.str, elem.asnlen);
	    if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "} "));
	    }
	}

	if (ndo->ndo_vflag) {
	    ND_PRINT((ndo, "{ ScopedPDU "));
	}

	scopedpdu_print(ndo, np, length, 3);

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "} "));
	}
}