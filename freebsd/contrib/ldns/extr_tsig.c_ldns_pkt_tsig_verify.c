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
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int ldns_pkt_tsig_verify_next (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

bool
ldns_pkt_tsig_verify(ldns_pkt *pkt, const uint8_t *wire, size_t wirelen, const char *key_name,
	const char *key_data, const ldns_rdf *orig_mac_rdf)
{
	return ldns_pkt_tsig_verify_next(pkt, wire, wirelen, key_name, key_data, orig_mac_rdf, 0);
}