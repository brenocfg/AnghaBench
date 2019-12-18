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
struct trust_anchor {size_t numDNSKEY; int /*<<< orphan*/  dnskey_rrset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dnskey_algo_is_supported (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static size_t
anchors_dnskey_unsupported(struct trust_anchor* ta)
{
	size_t i, num = 0;
	for(i=0; i<ta->numDNSKEY; i++) {
		if(!dnskey_algo_is_supported(ta->dnskey_rrset, i))
			num++;
	}
	return num;
}