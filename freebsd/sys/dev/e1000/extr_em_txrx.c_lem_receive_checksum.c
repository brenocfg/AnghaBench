#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_rxd_info_t ;
struct TYPE_3__ {int iri_csum_flags; int /*<<< orphan*/  iri_csum_data; } ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int E1000_RXD_ERR_IPE ; 
 int E1000_RXD_ERR_TCPE ; 
 int E1000_RXD_STAT_IPCS ; 
 int E1000_RXD_STAT_TCPCS ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
lem_receive_checksum(int status, int errors, if_rxd_info_t ri)
{
	/* Did it pass? */
	if (status & E1000_RXD_STAT_IPCS && !(errors & E1000_RXD_ERR_IPE))
		ri->iri_csum_flags = (CSUM_IP_CHECKED|CSUM_IP_VALID);

	if (status & E1000_RXD_STAT_TCPCS) {
		/* Did it pass? */
		if (!(errors & E1000_RXD_ERR_TCPE)) {
			ri->iri_csum_flags |=
			(CSUM_DATA_VALID | CSUM_PSEUDO_HDR);
			ri->iri_csum_data = htons(0xffff);
		}
	}
}