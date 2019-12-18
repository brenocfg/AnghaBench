#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct auth_zone {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_rrset {TYPE_1__* data; } ;
struct auth_data {int dummy; } ;
struct TYPE_2__ {size_t count; size_t** rr_data; size_t* rr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3PARAM ; 
 size_t NSEC3_UNKNOWN_FLAGS ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec3_hash_algo_size_supported (int) ; 
 size_t sldns_read_uint16 (size_t*) ; 

__attribute__((used)) static int
az_nsec3_param(struct auth_zone* z, int* algo, size_t* iter, uint8_t** salt,
	size_t* saltlen)
{
	struct auth_data* apex;
	struct auth_rrset* param;
	size_t i;
	apex = az_find_name(z, z->name, z->namelen);
	if(!apex) return 0;
	param = az_domain_rrset(apex, LDNS_RR_TYPE_NSEC3PARAM);
	if(!param || param->data->count==0)
		return 0; /* no RRset or no RRs in rrset */
	/* find out which NSEC3PARAM RR has supported parameters */
	/* skip unknown flags (dynamic signer is recalculating nsec3 chain) */
	for(i=0; i<param->data->count; i++) {
		uint8_t* rdata = param->data->rr_data[i]+2;
		size_t rdatalen = param->data->rr_len[i];
		if(rdatalen < 2+5)
			continue; /* too short */
		if(!nsec3_hash_algo_size_supported((int)(rdata[0])))
			continue; /* unsupported algo */
		if(rdatalen < (size_t)(2+5+(size_t)rdata[4]))
			continue; /* salt missing */
		if((rdata[1]&NSEC3_UNKNOWN_FLAGS)!=0)
			continue; /* unknown flags */
		*algo = (int)(rdata[0]);
		*iter = sldns_read_uint16(rdata+2);
		*saltlen = rdata[4];
		if(*saltlen == 0)
			*salt = NULL;
		else	*salt = rdata+5;
		return 1;
	}
	/* no supported params */
	return 0;
}