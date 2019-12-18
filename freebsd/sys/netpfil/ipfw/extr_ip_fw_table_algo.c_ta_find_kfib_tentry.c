#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct table_info {int /*<<< orphan*/  data; } ;
struct sockaddr_in6 {int sin6_len; scalar_t__ sin6_family; int rti_addrs; int /*<<< orphan*/  sin6_addr; struct sockaddr** rti_info; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct rt_addrinfo {int sin6_len; scalar_t__ sin6_family; int rti_addrs; int /*<<< orphan*/  sin6_addr; struct sockaddr** rti_info; } ;
typedef  int /*<<< orphan*/  mask6 ;
typedef  int /*<<< orphan*/  key6 ;
struct TYPE_5__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {scalar_t__ subtype; TYPE_1__ k; } ;
typedef  TYPE_2__ ipfw_obj_tentry ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  dst6 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ENOENT ; 
 size_t RTAX_DST ; 
 size_t RTAX_NETMASK ; 
 int RTA_NETMASK ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 scalar_t__ rib_lookup_info (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 
 int /*<<< orphan*/  ta_dump_kfib_tentry_int (struct sockaddr*,struct sockaddr*,TYPE_2__*) ; 

__attribute__((used)) static int
ta_find_kfib_tentry(void *ta_state, struct table_info *ti,
    ipfw_obj_tentry *tent)
{
	struct rt_addrinfo info;
	struct sockaddr_in6 key6, dst6, mask6;
	struct sockaddr *dst, *key, *mask;

	/* Prepare sockaddr for prefix/mask and info */
	bzero(&dst6, sizeof(dst6));
	dst6.sin6_len = sizeof(dst6);
	dst = (struct sockaddr *)&dst6;
	bzero(&mask6, sizeof(mask6));
	mask6.sin6_len = sizeof(mask6);
	mask = (struct sockaddr *)&mask6;

	bzero(&info, sizeof(info));
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_NETMASK] = mask;

	/* Prepare the lookup key */
	bzero(&key6, sizeof(key6));
	key6.sin6_family = tent->subtype;
	key = (struct sockaddr *)&key6;

	if (tent->subtype == AF_INET) {
		((struct sockaddr_in *)&key6)->sin_addr = tent->k.addr;
		key6.sin6_len = sizeof(struct sockaddr_in);
	} else {
		key6.sin6_addr = tent->k.addr6;
		key6.sin6_len = sizeof(struct sockaddr_in6);
	}

	if (rib_lookup_info(ti->data, key, 0, 0, &info) != 0)
		return (ENOENT);
	if ((info.rti_addrs & RTA_NETMASK) == 0)
		mask = NULL;

	ta_dump_kfib_tentry_int(dst, mask, tent);

	return (0);
}