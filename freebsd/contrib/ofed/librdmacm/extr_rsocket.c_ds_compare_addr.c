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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int memcmp (void const*,void const*,size_t) ; 

__attribute__((used)) static int ds_compare_addr(const void *dst1, const void *dst2)
{
	const struct sockaddr *sa1, *sa2;
	size_t len;

	sa1 = (const struct sockaddr *) dst1;
	sa2 = (const struct sockaddr *) dst2;

	len = (sa1->sa_family == AF_INET6 && sa2->sa_family == AF_INET6) ?
	      sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in);
	return memcmp(dst1, dst2, len);
}