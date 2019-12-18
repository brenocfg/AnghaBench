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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXTRACT_8BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2tp_cc_direction2str ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l2tp_ppp_discon_cc_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint16_t *ptr = (const uint16_t *)dat;

	if (length < 5) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	/* Disconnect Code */
	ND_PRINT((ndo, "%04x, ", EXTRACT_16BITS(dat)));
	dat += 2;
	length -= 2;
	/* Control Protocol Number */
	ND_PRINT((ndo, "%04x ",  EXTRACT_16BITS(dat)));
	dat += 2;
	length -= 2;
	/* Direction */
	ND_PRINT((ndo, "%s", tok2str(l2tp_cc_direction2str,
			     "Direction-#%u", EXTRACT_8BITS(ptr))));
	ptr++;
	length--;

	if (length != 0) {
		ND_PRINT((ndo, " "));
		print_string(ndo, (const u_char *)ptr, length);
	}
}