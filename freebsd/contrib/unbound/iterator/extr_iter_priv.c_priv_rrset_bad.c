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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {struct sockaddr_storage sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; struct sockaddr_storage sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {struct sockaddr_storage sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; struct sockaddr_storage sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct rrset_parse {scalar_t__ type; struct rr_parse* rr_first; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  dname; } ;
struct rr_parse {struct sockaddr_in6* ttl_data; struct rr_parse* next; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct iter_priv {TYPE_1__ a; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  sa ;
typedef  void* in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ INET6_SIZE ; 
 scalar_t__ INET_SIZE ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct sockaddr_storage*,struct sockaddr_in6*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ priv_lookup_addr (struct iter_priv*,struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ priv_lookup_name (struct iter_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_rr (char*,int /*<<< orphan*/ *,struct rrset_parse*,struct rr_parse*,struct rr_parse**,struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ sldns_read_uint16 (struct sockaddr_in6*) ; 

int priv_rrset_bad(struct iter_priv* priv, sldns_buffer* pkt,
	struct rrset_parse* rrset)
{
	if(priv->a.count == 0) 
		return 0; /* there are no blocked addresses */

	/* see if it is a private name, that is allowed to have any */
	if(priv_lookup_name(priv, pkt, rrset->dname, rrset->dname_len,
		ntohs(rrset->rrset_class))) {
		return 0;
	} else {
		/* so its a public name, check the address */
		socklen_t len;
		struct rr_parse* rr, *prev = NULL;
		if(rrset->type == LDNS_RR_TYPE_A) {
			struct sockaddr_storage addr;
			struct sockaddr_in sa;

			len = (socklen_t)sizeof(sa);
			memset(&sa, 0, len);
			sa.sin_family = AF_INET;
			sa.sin_port = (in_port_t)htons(UNBOUND_DNS_PORT);
			for(rr = rrset->rr_first; rr; rr = rr->next) {
				if(sldns_read_uint16(rr->ttl_data+4) 
					!= INET_SIZE) {
					prev = rr;
					continue;
				}
				memmove(&sa.sin_addr, rr->ttl_data+4+2, 
					INET_SIZE);
				memmove(&addr, &sa, len);
				if(priv_lookup_addr(priv, &addr, len)) {
					if(remove_rr("sanitize: removing public name with private address", pkt, rrset, prev, &rr, &addr, len))
						return 1;
					continue;
				}
				prev = rr;
			}
		} else if(rrset->type == LDNS_RR_TYPE_AAAA) {
			struct sockaddr_storage addr;
			struct sockaddr_in6 sa;
			len = (socklen_t)sizeof(sa);
			memset(&sa, 0, len);
			sa.sin6_family = AF_INET6;
			sa.sin6_port = (in_port_t)htons(UNBOUND_DNS_PORT);
			for(rr = rrset->rr_first; rr; rr = rr->next) {
				if(sldns_read_uint16(rr->ttl_data+4) 
					!= INET6_SIZE) {
					prev = rr;
					continue;
				}
				memmove(&sa.sin6_addr, rr->ttl_data+4+2, 
					INET6_SIZE);
				memmove(&addr, &sa, len);
				if(priv_lookup_addr(priv, &addr, len)) {
					if(remove_rr("sanitize: removing public name with private address", pkt, rrset, prev, &rr, &addr, len))
						return 1;
					continue;
				}
				prev = rr;
			}
		} 
	}
	return 0;
}