#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_flowinfo; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
union socket_addr {TYPE_6__ sin6; TYPE_3__ sin; TYPE_1__ sa; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  flowinfo; } ;
struct TYPE_11__ {TYPE_4__ ipv6; int /*<<< orphan*/  ipv4; } ;
struct ds_header {int version; TYPE_5__ addr; int /*<<< orphan*/  port; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DS_IPV4_HDR_LEN ; 
 int /*<<< orphan*/  DS_IPV6_HDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ds_format_hdr(struct ds_header *hdr, union socket_addr *addr)
{
	if (addr->sa.sa_family == AF_INET) {
		hdr->version = 4;
		hdr->length = DS_IPV4_HDR_LEN;
		hdr->port = addr->sin.sin_port;
		hdr->addr.ipv4 = addr->sin.sin_addr.s_addr;
	} else {
		hdr->version = 6;
		hdr->length = DS_IPV6_HDR_LEN;
		hdr->port = addr->sin6.sin6_port;
		hdr->addr.ipv6.flowinfo= addr->sin6.sin6_flowinfo;
		memcpy(&hdr->addr.ipv6.addr, &addr->sin6.sin6_addr, 16);
	}
}