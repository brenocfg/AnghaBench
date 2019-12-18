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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  dname_len; int /*<<< orphan*/  dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {size_t count; scalar_t__* rr_len; scalar_t__ security; scalar_t__* rr_data; } ;
struct delegpt {int /*<<< orphan*/  dp_type_mlc; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  scalar_t__ in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ INET6_SIZE ; 
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  delegpt_add_target (struct delegpt*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_status_bogus ; 

int 
delegpt_add_rrset_AAAA(struct delegpt* dp, struct regional* region,
	struct ub_packed_rrset_key* ak, uint8_t lame)
{
        struct packed_rrset_data* d=(struct packed_rrset_data*)ak->entry.data;
        size_t i;
        struct sockaddr_in6 sa;
        socklen_t len = (socklen_t)sizeof(sa);
	log_assert(!dp->dp_type_mlc);
        memset(&sa, 0, len);
        sa.sin6_family = AF_INET6;
        sa.sin6_port = (in_port_t)htons(UNBOUND_DNS_PORT);
        for(i=0; i<d->count; i++) {
                if(d->rr_len[i] != 2 + INET6_SIZE) /* rdatalen + len of IP6 */
                        continue;
                memmove(&sa.sin6_addr, d->rr_data[i]+2, INET6_SIZE);
                if(!delegpt_add_target(dp, region, ak->rk.dname,
                        ak->rk.dname_len, (struct sockaddr_storage*)&sa,
                        len, (d->security==sec_status_bogus), lame))
                        return 0;
        }
        return 1;
}