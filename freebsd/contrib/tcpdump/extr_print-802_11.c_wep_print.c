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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_LE_32BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ IEEE802_11_IV_LEN ; 
 scalar_t__ IEEE802_11_KID_LEN ; 
 int /*<<< orphan*/  IV_IV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IV_KEYID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IV_PAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 

__attribute__((used)) static int
wep_print(netdissect_options *ndo,
          const u_char *p)
{
	uint32_t iv;

	if (!ND_TTEST2(*p, IEEE802_11_IV_LEN + IEEE802_11_KID_LEN))
		return 0;
	iv = EXTRACT_LE_32BITS(p);

	ND_PRINT((ndo, " IV:%3x Pad %x KeyID %x", IV_IV(iv), IV_PAD(iv),
	    IV_KEYID(iv)));

	return 1;
}