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
struct ub_packed_rrset_key {int dummy; } ;
struct resp_addr {struct ub_packed_rrset_key* data; } ;

/* Variables and functions */

struct ub_packed_rrset_key*
resp_addr_get_rrset(struct resp_addr* addr)
{
	return addr ? addr->data : NULL;
}