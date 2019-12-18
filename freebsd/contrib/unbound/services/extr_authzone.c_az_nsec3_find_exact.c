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
struct auth_zone {int dummy; } ;
struct auth_data {int dummy; } ;
typedef  int /*<<< orphan*/  hname ;

/* Variables and functions */
 int LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  az_nsec3_hashname (struct auth_zone*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct auth_data*
az_nsec3_find_exact(struct auth_zone* z, uint8_t* nm, size_t nmlen,
	int algo, size_t iter, uint8_t* salt, size_t saltlen)
{
	struct auth_data* node;
	uint8_t hname[LDNS_MAX_DOMAINLEN];
	size_t hlen = sizeof(hname);
	if(!az_nsec3_hashname(z, hname, &hlen, nm, nmlen, algo, iter,
		salt, saltlen))
		return NULL;
	node = az_find_name(z, hname, hlen);
	if(az_domain_rrset(node, LDNS_RR_TYPE_NSEC3))
		return node;
	return NULL;
}