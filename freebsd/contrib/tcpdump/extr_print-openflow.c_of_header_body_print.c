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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int OF_HEADER_LEN ; 
#define  OF_VER_1_0 128 
 int /*<<< orphan*/  istr ; 
 int const* of10_header_body_print (int /*<<< orphan*/ *,int const*,int const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_header_print (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of_header_body_print(netdissect_options *ndo, const u_char *cp, const u_char *ep)
{
	uint8_t version, type;
	uint16_t length;
	uint32_t xid;

	if (ep < cp + OF_HEADER_LEN)
		goto invalid;
	/* version */
	ND_TCHECK2(*cp, 1);
	version = *cp;
	cp += 1;
	/* type */
	ND_TCHECK2(*cp, 1);
	type = *cp;
	cp += 1;
	/* length */
	ND_TCHECK2(*cp, 2);
	length = EXTRACT_16BITS(cp);
	cp += 2;
	/* xid */
	ND_TCHECK2(*cp, 4);
	xid = EXTRACT_32BITS(cp);
	cp += 4;
	/* Message length includes the header length and a message always includes
	 * the basic header. A message length underrun fails decoding of the rest of
	 * the current packet. At the same time, try decoding as much of the current
	 * message as possible even when it does not end within the current TCP
	 * segment. */
	if (length < OF_HEADER_LEN) {
		of_header_print(ndo, version, type, length, xid);
		goto invalid;
	}
	/* Decode known protocol versions further without printing the header (the
	 * type decoding is version-specific. */
	switch (version) {
	case OF_VER_1_0:
		return of10_header_body_print(ndo, cp, ep, type, length, xid);
	default:
		of_header_print(ndo, version, type, length, xid);
		ND_TCHECK2(*cp, length - OF_HEADER_LEN);
		return cp + length - OF_HEADER_LEN; /* done with current message */
	}

invalid: /* fail current packet */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return ep;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}