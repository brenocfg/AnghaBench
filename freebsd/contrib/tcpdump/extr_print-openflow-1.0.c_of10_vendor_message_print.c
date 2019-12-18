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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int const) ; 
 scalar_t__ OUI_BSN ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  const* of10_bsn_message_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* of10_data_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  of_vendor_name (scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_vendor_message_print(netdissect_options *ndo,
                          const u_char *cp, const u_char *ep, const u_int len)
{
	uint32_t vendor;
	const u_char *(*decoder)(netdissect_options *, const u_char *, const u_char *, u_int);

	if (len < 4)
		goto invalid;
	/* vendor */
	ND_TCHECK2(*cp, 4);
	vendor = EXTRACT_32BITS(cp);
	cp += 4;
	ND_PRINT((ndo, ", vendor 0x%08x (%s)", vendor, of_vendor_name(vendor)));
	/* data */
	decoder =
		vendor == OUI_BSN         ? of10_bsn_message_print         :
		of10_data_print;
	return decoder(ndo, cp, ep, len - 4);

invalid: /* skip the undersized data */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, len);
	return cp + len;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}