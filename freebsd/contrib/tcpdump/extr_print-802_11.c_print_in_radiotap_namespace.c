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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct cpack_state {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  enum ieee80211_radiotap_type { ____Placeholder_ieee80211_radiotap_type } ieee80211_radiotap_type ;

/* Variables and functions */
 int BITNO_32 (int) ; 
 int IEEE80211_RADIOTAP_NAMESPACE ; 
 int print_radiotap_field (int /*<<< orphan*/ *,struct cpack_state*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
print_in_radiotap_namespace(netdissect_options *ndo,
                            struct cpack_state *s, uint8_t *flags,
                            uint32_t presentflags, int bit0)
{
#define	BITNO_32(x) (((x) >> 16) ? 16 + BITNO_16((x) >> 16) : BITNO_16((x)))
#define	BITNO_16(x) (((x) >> 8) ? 8 + BITNO_8((x) >> 8) : BITNO_8((x)))
#define	BITNO_8(x) (((x) >> 4) ? 4 + BITNO_4((x) >> 4) : BITNO_4((x)))
#define	BITNO_4(x) (((x) >> 2) ? 2 + BITNO_2((x) >> 2) : BITNO_2((x)))
#define	BITNO_2(x) (((x) & 2) ? 1 : 0)
	uint32_t present, next_present;
	int bitno;
	enum ieee80211_radiotap_type bit;
	int rc;

	for (present = presentflags; present; present = next_present) {
		/*
		 * Clear the least significant bit that is set.
		 */
		next_present = present & (present - 1);

		/*
		 * Get the bit number, within this presence word,
		 * of the remaining least significant bit that
		 * is set.
		 */
		bitno = BITNO_32(present ^ next_present);

		/*
		 * Stop if this is one of the "same meaning
		 * in all presence flags" bits.
		 */
		if (bitno >= IEEE80211_RADIOTAP_NAMESPACE)
			break;

		/*
		 * Get the radiotap bit number of that bit.
		 */
		bit = (enum ieee80211_radiotap_type)(bit0 + bitno);

		rc = print_radiotap_field(ndo, s, bit, flags, presentflags);
		if (rc != 0)
			return rc;
	}

	return 0;
}