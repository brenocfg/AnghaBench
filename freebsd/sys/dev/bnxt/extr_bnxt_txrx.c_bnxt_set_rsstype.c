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
typedef  int uint8_t ;
typedef  TYPE_1__* if_rxd_info_t ;
struct TYPE_3__ {int /*<<< orphan*/  iri_rsstype; } ;

/* Variables and functions */
 int BNXT_GET_RSS_PROFILE_ID (int) ; 
#define  BNXT_RSS_HASH_TYPE_IPV4 133 
#define  BNXT_RSS_HASH_TYPE_IPV6 132 
#define  BNXT_RSS_HASH_TYPE_TCPV4 131 
#define  BNXT_RSS_HASH_TYPE_TCPV6 130 
#define  BNXT_RSS_HASH_TYPE_UDPV4 129 
#define  BNXT_RSS_HASH_TYPE_UDPV6 128 
 int /*<<< orphan*/  M_HASHTYPE_OPAQUE_HASH ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_IPV6 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_TCP_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_TCP_IPV6 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_UDP_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_UDP_IPV6 ; 

__attribute__((used)) static void
bnxt_set_rsstype(if_rxd_info_t ri, uint8_t rss_hash_type)
{
	uint8_t rss_profile_id;

	rss_profile_id = BNXT_GET_RSS_PROFILE_ID(rss_hash_type);
	switch (rss_profile_id) {
	case BNXT_RSS_HASH_TYPE_TCPV4:
		ri->iri_rsstype = M_HASHTYPE_RSS_TCP_IPV4;
		break;
	case BNXT_RSS_HASH_TYPE_UDPV4:
		ri->iri_rsstype = M_HASHTYPE_RSS_UDP_IPV4;
		break;
	case BNXT_RSS_HASH_TYPE_IPV4:
		ri->iri_rsstype = M_HASHTYPE_RSS_IPV4;
		break;
	case BNXT_RSS_HASH_TYPE_TCPV6:
		ri->iri_rsstype = M_HASHTYPE_RSS_TCP_IPV6;
		break;
	case BNXT_RSS_HASH_TYPE_UDPV6:
		ri->iri_rsstype = M_HASHTYPE_RSS_UDP_IPV6;
		break;
	case BNXT_RSS_HASH_TYPE_IPV6:
		ri->iri_rsstype = M_HASHTYPE_RSS_IPV6;
		break;
	default:
		ri->iri_rsstype = M_HASHTYPE_OPAQUE_HASH;
		break;
	}
}