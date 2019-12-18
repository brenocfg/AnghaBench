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
struct if_ath_alq_init_state {int /*<<< orphan*/  sc_hal_magic; int /*<<< orphan*/  sc_phy_rev; int /*<<< orphan*/  sc_mac_revision; int /*<<< orphan*/  sc_mac_version; } ;

/* Variables and functions */
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static void
ath_alq_print_hdr(struct if_ath_alq_init_state *hdr)
{
	printf("macVersion=%d.%d, PHY=%d, Magic=%08x\n",
	    be32toh(hdr->sc_mac_version),
	    be32toh(hdr->sc_mac_revision),
	    be32toh(hdr->sc_phy_rev),
	    be32toh(hdr->sc_hal_magic));
}