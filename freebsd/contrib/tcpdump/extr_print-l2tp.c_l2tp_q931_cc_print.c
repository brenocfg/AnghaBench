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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_16bits_val (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
l2tp_q931_cc_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	if (length < 3) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	print_16bits_val(ndo, (const uint16_t *)dat);
	ND_PRINT((ndo, ", %02x", dat[2]));
	dat += 3;
	length -= 3;
	if (length != 0) {
		ND_PRINT((ndo, " "));
		print_string(ndo, dat, length);
	}
}