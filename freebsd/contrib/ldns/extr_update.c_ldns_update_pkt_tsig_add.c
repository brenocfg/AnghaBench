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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_pkt_tsig_sign (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_tsig_algorithm (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_resolver_tsig_keydata (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_resolver_tsig_keyname (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_update_pkt_tsig_add(ldns_pkt *p, const ldns_resolver *r)
{
#ifdef HAVE_SSL
	uint16_t fudge = 300; /* Recommended fudge. [RFC2845 6.4]  */
	if (ldns_resolver_tsig_keyname(r) && ldns_resolver_tsig_keydata(r))
		return ldns_pkt_tsig_sign(p, ldns_resolver_tsig_keyname(r),
		    ldns_resolver_tsig_keydata(r), fudge,
		    ldns_resolver_tsig_algorithm(r), NULL);
#else
	/* do nothing */
	(void)p;
	(void)r;
#endif /* HAVE_SSL */
	/* No TSIG to do. */
	return LDNS_STATUS_OK;
}