#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_family; scalar_t__ sa_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  key_bbcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* satosin (struct sockaddr const*) ; 
 TYPE_1__* satosin6 (struct sockaddr const*) ; 

int
key_sockaddrcmp_withmask(const struct sockaddr *sa1,
    const struct sockaddr *sa2, size_t mask)
{
	if (sa1->sa_family != sa2->sa_family || sa1->sa_len != sa2->sa_len)
		return (1);

	switch (sa1->sa_family) {
#ifdef INET
	case AF_INET:
		return (!key_bbcmp(&satosin(sa1)->sin_addr,
		    &satosin(sa2)->sin_addr, mask));
#endif
#ifdef INET6
	case AF_INET6:
		if (satosin6(sa1)->sin6_scope_id !=
		    satosin6(sa2)->sin6_scope_id)
			return (1);
		return (!key_bbcmp(&satosin6(sa1)->sin6_addr,
		    &satosin6(sa2)->sin6_addr, mask));
#endif
	}
	return (1);
}