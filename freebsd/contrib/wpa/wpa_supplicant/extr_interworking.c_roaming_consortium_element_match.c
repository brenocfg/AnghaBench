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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ os_memcmp (int const*,int const*,size_t) ; 

__attribute__((used)) static int roaming_consortium_element_match(const u8 *ie, const u8 *rc_id,
					    size_t rc_len)
{
	const u8 *pos, *end;
	u8 lens;

	if (ie == NULL)
		return 0;

	pos = ie + 2;
	end = ie + 2 + ie[1];

	/* Roaming Consortium element:
	 * Number of ANQP OIs
	 * OI #1 and #2 lengths
	 * OI #1, [OI #2], [OI #3]
	 */

	if (end - pos < 2)
		return 0;

	pos++; /* skip Number of ANQP OIs */
	lens = *pos++;
	if ((lens & 0x0f) + (lens >> 4) > end - pos)
		return 0;

	if ((lens & 0x0f) == rc_len && os_memcmp(pos, rc_id, rc_len) == 0)
		return 1;
	pos += lens & 0x0f;

	if ((lens >> 4) == rc_len && os_memcmp(pos, rc_id, rc_len) == 0)
		return 1;
	pos += lens >> 4;

	if (pos < end && (size_t) (end - pos) == rc_len &&
	    os_memcmp(pos, rc_id, rc_len) == 0)
		return 1;

	return 0;
}