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
struct peer_address {int size; void* address; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

__attribute__((used)) static inline int create_peer_from_gid(int family, void *raw_gid,
				       struct peer_address *peer_address)
{
	switch (family) {
	case AF_INET:
		peer_address->address = raw_gid + 12;
		peer_address->size = 4;
		break;
	case AF_INET6:
		peer_address->address = raw_gid;
		peer_address->size = 16;
		break;
	default:
		return -1;
	}

	return 0;
}