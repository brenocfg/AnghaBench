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
struct bwn_mac {int mac_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_MACCMD ; 
 int BWN_MACCMD_DFQ_VALID ; 
 int BWN_MAC_FLAG_DFQVALID ; 
 int BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_intr_atim_end(struct bwn_mac *mac)
{

	if (mac->mac_flags & BWN_MAC_FLAG_DFQVALID) {
		BWN_WRITE_4(mac, BWN_MACCMD,
		    BWN_READ_4(mac, BWN_MACCMD) | BWN_MACCMD_DFQ_VALID);
		mac->mac_flags &= ~BWN_MAC_FLAG_DFQVALID;
	}
}