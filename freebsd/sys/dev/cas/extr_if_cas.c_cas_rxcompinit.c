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
struct ip {int dummy; } ;
struct cas_rx_comp {void* crc_word4; void* crc_word3; scalar_t__ crc_word2; scalar_t__ crc_word1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_RC3_CSO ; 
 int /*<<< orphan*/  CAS_RC4_ZERO ; 
 int /*<<< orphan*/  CAS_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ETHER_HDR_LEN ; 
 void* htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
cas_rxcompinit(struct cas_rx_comp *rxcomp)
{

	rxcomp->crc_word1 = 0;
	rxcomp->crc_word2 = 0;
	rxcomp->crc_word3 =
	    htole64(CAS_SET(ETHER_HDR_LEN + sizeof(struct ip), CAS_RC3_CSO));
	rxcomp->crc_word4 = htole64(CAS_RC4_ZERO);
}