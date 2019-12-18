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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct module_env {int /*<<< orphan*/  rrset_cache; } ;

/* Variables and functions */
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
find_closest_of_type(struct module_env* env, uint8_t* qname, size_t qnamelen, 
	uint16_t qclass, time_t now, uint16_t searchtype, int stripfront)
{
	struct ub_packed_rrset_key *rrset;
	uint8_t lablen;

	if(stripfront) {
		/* strip off so that DNAMEs have strict subdomain match */
		lablen = *qname;
		qname += lablen + 1;
		qnamelen -= lablen + 1;
	}

	/* snip off front part of qname until the type is found */
	while(qnamelen > 0) {
		if((rrset = rrset_cache_lookup(env->rrset_cache, qname, 
			qnamelen, searchtype, qclass, 0, now, 0)))
			return rrset;

		/* snip off front label */
		lablen = *qname;
		qname += lablen + 1;
		qnamelen -= lablen + 1;
	}
	return NULL;
}