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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; scalar_t__ sin6_port; struct sockaddr_storage sin6_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; scalar_t__ sin_port; struct sockaddr_storage sin_addr; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ INET6_SIZE ; 
 scalar_t__ INET_SIZE ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int memcmp (struct sockaddr_storage*,struct sockaddr_storage*,scalar_t__) ; 

int
sockaddr_cmp(struct sockaddr_storage* addr1, socklen_t len1, 
	struct sockaddr_storage* addr2, socklen_t len2)
{
	struct sockaddr_in* p1_in = (struct sockaddr_in*)addr1;
	struct sockaddr_in* p2_in = (struct sockaddr_in*)addr2;
	struct sockaddr_in6* p1_in6 = (struct sockaddr_in6*)addr1;
	struct sockaddr_in6* p2_in6 = (struct sockaddr_in6*)addr2;
	if(len1 < len2)
		return -1;
	if(len1 > len2)
		return 1;
	log_assert(len1 == len2);
	if( p1_in->sin_family < p2_in->sin_family)
		return -1;
	if( p1_in->sin_family > p2_in->sin_family)
		return 1;
	log_assert( p1_in->sin_family == p2_in->sin_family );
	/* compare ip4 */
	if( p1_in->sin_family == AF_INET ) {
		/* just order it, ntohs not required */
		if(p1_in->sin_port < p2_in->sin_port)
			return -1;
		if(p1_in->sin_port > p2_in->sin_port)
			return 1;
		log_assert(p1_in->sin_port == p2_in->sin_port);
		return memcmp(&p1_in->sin_addr, &p2_in->sin_addr, INET_SIZE);
	} else if (p1_in6->sin6_family == AF_INET6) {
		/* just order it, ntohs not required */
		if(p1_in6->sin6_port < p2_in6->sin6_port)
			return -1;
		if(p1_in6->sin6_port > p2_in6->sin6_port)
			return 1;
		log_assert(p1_in6->sin6_port == p2_in6->sin6_port);
		return memcmp(&p1_in6->sin6_addr, &p2_in6->sin6_addr, 
			INET6_SIZE);
	} else {
		/* eek unknown type, perform this comparison for sanity. */
		return memcmp(addr1, addr2, len1);
	}
}