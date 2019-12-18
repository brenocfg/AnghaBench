#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {scalar_t__ raw; } ;
struct be {scalar_t__ type; int asnlen; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ BE_SEQ ; 
 scalar_t__ BE_STR ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int asn1_parse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,struct be*) ; 
 int /*<<< orphan*/  asn1_print (int /*<<< orphan*/ *,struct be*) ; 
 int asn1_print_octets (int /*<<< orphan*/ *,struct be*) ; 
 int asn1_print_string (int /*<<< orphan*/ *,struct be*) ; 
 int /*<<< orphan*/  pdu_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void
scopedpdu_print(netdissect_options *ndo,
                const u_char *np, u_int length, int version)
{
	struct be elem;
	int count = 0;

	/* Sequence */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_SEQ) {
		ND_PRINT((ndo, "[!scoped PDU]"));
		asn1_print(ndo, &elem);
		return;
	}
	length = elem.asnlen;
	np = (const u_char *)elem.data.raw;

	/* contextEngineID (OCTET STRING) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		ND_PRINT((ndo, "[contextEngineID!=STR]"));
		asn1_print(ndo, &elem);
		return;
	}
	length -= count;
	np += count;

	ND_PRINT((ndo, "E="));
	if (asn1_print_octets(ndo, &elem) == -1)
		return;
	ND_PRINT((ndo, " "));

	/* contextName (OCTET STRING) */
	if ((count = asn1_parse(ndo, np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		ND_PRINT((ndo, "[contextName!=STR]"));
		asn1_print(ndo, &elem);
		return;
	}
	length -= count;
	np += count;

	ND_PRINT((ndo, "C="));
	if (asn1_print_string(ndo, &elem) == -1)
		return;
	ND_PRINT((ndo, " "));

	pdu_print(ndo, np, length, version);
}