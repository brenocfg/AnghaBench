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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_pkt_tsig_sign_next (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ldns_status
ldns_pkt_tsig_sign(ldns_pkt *pkt, const char *key_name, const char *key_data,
	uint16_t fudge, const char *algorithm_name, const ldns_rdf *query_mac)
{
	return ldns_pkt_tsig_sign_next(pkt, key_name, key_data, fudge, algorithm_name, query_mac, 0);
}