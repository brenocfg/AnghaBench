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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
l2tp_result_code_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint16_t *ptr = (const uint16_t *)dat;

	/* Result Code */
	if (length < 2) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	ND_PRINT((ndo, "%u", EXTRACT_16BITS(ptr)));
	ptr++;
	length -= 2;

	/* Error Code (opt) */
	if (length == 0)
		return;
	if (length < 2) {
		ND_PRINT((ndo, " AVP too short"));
		return;
	}
	ND_PRINT((ndo, "/%u", EXTRACT_16BITS(ptr)));
	ptr++;
	length -= 2;

	/* Error Message (opt) */
	if (length == 0)
		return;
	ND_PRINT((ndo, " "));
	print_string(ndo, (const u_char *)ptr, length);
}