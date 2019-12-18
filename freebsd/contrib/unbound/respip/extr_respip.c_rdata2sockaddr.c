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
typedef  scalar_t__ uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct packed_rrset_data {int* rr_len; scalar_t__* rr_data; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rdata2sockaddr(const struct packed_rrset_data* rd, uint16_t rtype, size_t i,
	struct sockaddr_storage* ss, socklen_t* addrlenp)
{
	/* unbound can accept and cache odd-length AAAA/A records, so we have
	 * to validate the length. */
	if(rtype == LDNS_RR_TYPE_A && rd->rr_len[i] == 6) {
		struct sockaddr_in* sa4 = (struct sockaddr_in*)ss;

		memset(sa4, 0, sizeof(*sa4));
		sa4->sin_family = AF_INET;
		memcpy(&sa4->sin_addr, rd->rr_data[i] + 2,
			sizeof(sa4->sin_addr));
		*addrlenp = sizeof(*sa4);
		return 1;
	} else if(rtype == LDNS_RR_TYPE_AAAA && rd->rr_len[i] == 18) {
		struct sockaddr_in6* sa6 = (struct sockaddr_in6*)ss;

		memset(sa6, 0, sizeof(*sa6));
		sa6->sin6_family = AF_INET6;
		memcpy(&sa6->sin6_addr, rd->rr_data[i] + 2,
			sizeof(sa6->sin6_addr));
		*addrlenp = sizeof(*sa6);
		return 1;
	}
	return 0;
}